/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:19:14 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/05 13:41:37 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenisation.h"

static int	ft_tokencpy_env(t_global *global, char *src, char *dest, int *pos)
{
	char	*exit_stat;
	char	*env_var;
	int		idx;

	idx = 0;
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
		ft_sstrlcpy(dest + (*pos), env_var, ft_strlen(env_var) + 1);
		(*pos) += ft_strlen(env_var);
		idx += ft_envname_len(src + idx + 1);
	}
	return (idx);
}

int	ft_tokencpy(t_global *global, char *dest, char *src, int *pos)
{
	int	idx;
	int	tmp;

	tmp = 0;
	idx = 0;
	if (src[idx] == '$')
	{
		tmp = ft_tokencpy_env(global, src + idx, dest, pos);
		if (tmp == -1)
			return (-1);
		idx += tmp;
	}
	else
		dest[(*pos)++] = src[idx];
	idx++;
	return (idx);
}

static int	ft_quote_handle(t_global *global, char *str, char *dest, int *pos)
{
	int	idx;
	int	tmp;

	idx = 0;
	if (str[idx] && str[idx] == '"')
	{
		idx++;
		while (str[idx] && str[idx] != '"')
		{
			tmp = ft_tokencpy(global, dest, str + idx, pos);
			if (tmp == -1)
				return (-1);
			idx += tmp;
		}
		idx++;
	}
	if (str[idx] && str[idx] == '\'')
	{
		idx++;
		while (str[idx] && str[idx] != '\'')
			dest[(*pos)++] = str[idx++];
		idx++;
	}
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
		tmp = ft_quote_handle(global, str + idx, dest, &pos);
		if (tmp == -1)
			return (-1);
		idx += tmp;
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
	return (idx);
}
