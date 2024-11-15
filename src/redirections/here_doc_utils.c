/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:49:55 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 15:09:03 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_getsizelim(char *line)
{
	size_t	idx;
	size_t	len;
	size_t	tmp;

	len = 0;
	idx = 0;
	while (is_in_set(line[idx], " 	"))
		idx++;
	while (line[idx] && !is_in_set(line[idx], " 	"))
	{
		if (is_in_set(line[idx], "'\""))
		{
			tmp = ft_skipquotes(line + idx, line[idx]);
			len += tmp -2;
			idx += tmp;
		}
		else
		{
			len++;
			idx++;
		}
	}
	return (len);
}

char	*ft_hd_quotecpy(char *dest, char **src)
{
	int		i;
	char	quote;

	i = 0;
	quote = (*src)[0];
	while ((*src)[i + 1] && (*src)[i + 1] != quote)
	{
		dest[i] = (*src)[i + 1];
		i++;
	}
	(*src) = (*src) + i + 1;
	return (dest + i);
}

// malloc sensitive
char	*ft_getlim(t_global *global, char *line, int *in_quote)
{
	char	*result;
	char	*tmp;

	(void)global;
	line = line + 2;
	result = ft_calloc(ft_getsizelim(line) + 1, sizeof(char));
	if (!result)
		return (perr(ERR_ALLOC), NULL);
	tmp = result;
	while (is_in_set(*line, " 	"))
		line++;
	while (*line && !is_in_set(*line, " 	|><"))
	{
		if (is_in_set(*line, "'\""))
		{
			*in_quote = 1;
			tmp = ft_hd_quotecpy(tmp, &line);
		}
		else
			*(tmp++) = *line;
		line++;
	}
	*tmp = 0;
	return (result);
}

// malloc sensitive
char	*ft_init_hd_tk(t_global *global, char *line)
{
	int	idx;
	int	size;

	idx = 0;
	size = 0;
	while (line[idx])
	{
		if (line[idx] == '$')
		{
			size += ft_env_len_bis(global, line + idx + 1);
			if (size == -1)
				return (NULL);
			idx += ft_envname_len(line + idx + 1);
		}
		else
		{
			size++;
			idx++;
		}
	}
	return (ft_calloc(size + 1, sizeof(char)));
}

// malloc sensitive
char	*ft_fill_hd_tk(t_global *global, char *line, char *new_line)
{
	int		idx;
	int		size;
	char	*env_var;

	idx = 0;
	size = 0;
	while (line[idx])
	{
		if (line[idx] == '$')
		{
			env_var = ft_env_var(global, line + idx + 1);
			if (!env_var)
			{
				free(new_line);
				return (NULL);
			}
			ft_sstrlcpy(new_line + size, env_var, ft_strlen(env_var) + 1);
			size += ft_strlen(env_var);
			idx += ft_envname_len(line + idx + 1) + 1;
		}
		else
			new_line[size++] = line[idx++];
	}
	new_line[size] = 0;
	return (new_line);
}
