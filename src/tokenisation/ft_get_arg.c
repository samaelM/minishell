/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:19:14 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/11 20:03:14 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_tokencpy(t_global *global, char *dest, char *src, int *pos)
{
	int		idx;
	char	*exit_stat;

	idx = 0;
	if (src[idx] == '$')
	{
		if (src[idx + 1] == '?')
		{
			exit_stat = ft_itoa(global->exit_value);
			ft_sstrlcpy(dest + (*pos), exit_stat, ft_strlen(exit_stat) + 1);
			(*pos) += ft_strlen(exit_stat) + 1;
			free(exit_stat);
			idx++;
		}
		else
		{
			printf("pb\n");
			ft_sstrlcpy(dest + (*pos), ft_env_var(global, src + idx + 1),
				ft_env_len_bis(global, src + idx + 1) + 1);
			(*pos) += ft_env_len_bis(global, src + idx + 1);
			idx += ft_envname_len(src + idx + 1);
		}
	}
	else
		dest[(*pos)++] = src[idx];
	idx++;
	return (idx);
}

int	ft_get_arg(t_global *global, char *dest, char *str)
{
	int	idx;
	int	pos;

	pos = 0;
	idx = 0;
	while (str[idx] && is_in_set(str[idx], " 	"))
		idx++;
	while (str[idx] && !is_in_set(str[idx], " 	|"))
	{
		if (str[idx] && str[idx] == '"')
		{
			idx++;
			while (str[idx] && str[idx] != '"')
				idx += ft_tokencpy(global, dest, str + idx, &pos);
			idx++;
		}
		if (str[idx] && str[idx] == '\'')
		{
			idx++;
			while (str[idx] && str[idx] != '\'')
				dest[pos++] = str[idx++];
			idx++;
		}
		while (str[idx] && !is_in_set(str[idx], "\"' 	|<>"))
			idx += ft_tokencpy(global, dest, str + idx, &pos);
		while (str[idx] && is_in_set(str[idx], "<>"))
			idx += ft_redir_len(str + idx);
	}
	dest[pos] = 0;
	return (idx);
}
