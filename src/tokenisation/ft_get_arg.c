/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:19:14 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/18 17:51:40 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenisation.h"

static int	ft_tokencpy(t_global *global, char *dest, char *src, int *pos)
{
	int		idx;
	char	*exit_stat;
	char	*env_var;

	idx = 0;
	if (src[idx] == '$')
	{
		if (src[idx + 1] == '?')
		{
			exit_stat = ft_itoa(global->exit_value);
			if (!exit_stat)
				return (perr(ERR_ALLOC), -1);
			ft_sstrlcpy(dest + (*pos), exit_stat, ft_strlen(exit_stat) + 1);
			(*pos) += ft_strlen(exit_stat);
			free(exit_stat);
			idx++;
		}
		else
		{
			env_var = ft_env_var(global, src + idx + 1);
			if (!env_var)
				return (-1);
			ft_sstrlcpy(dest + (*pos), env_var, ft_strlen(env_var)+1);
			(*pos) += ft_strlen(env_var);
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
	int	tmp;

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
			{
				tmp = ft_tokencpy(global, dest, str + idx, &pos);
				if (tmp == -1)
					return (-1);
				idx += tmp;
			}
			if (str[idx])
				idx++;
		}
		if (str[idx] && str[idx] == '\'')
		{
			idx++;
			while (str[idx] && str[idx] != '\'')
				dest[pos++] = str[idx++];
			if (str[idx])
				idx++;
		}
		while (str[idx] && !is_in_set(str[idx], "\"' 	|<>"))
		{
			tmp = ft_tokencpy(global, dest, str + idx, &pos);
			if (tmp == -1)
				return (-1);
			idx += tmp;
		}
		while (str[idx] && is_in_set(str[idx], "<>"))
			idx += ft_redir_len(str + idx);
	}
	dest[pos] = 0;
	return (idx);
}
