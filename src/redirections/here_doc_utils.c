/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 17:49:55 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/13 15:26:04 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_getsizelim(char *line)
{
	size_t	idx;
	size_t	len;

	len = 0;
	idx = 0;
	while (is_in_set(line[idx], " 	"))
		idx++;
	while (line[idx] && !is_in_set(line[idx], " 	"))
	{
		if (!is_in_set(line[idx], "'\""))
			len++;
		idx++;
	}
	return (len);
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
		if (is_in_set(*line, "'\""))// copier toute la str d'un coup
			*in_quote = 1;
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

// malloc sensitive
char	*ft_hd_parse(t_global *global, char *line)
{
	char	*new_line;

	new_line = ft_init_hd_tk(global, line);
	if (!new_line)
		return (perr(ERR_ALLOC), NULL);
	new_line = ft_fill_hd_tk(global, line, new_line);
	if (!new_line)
		return (NULL);
	return (new_line);
}
