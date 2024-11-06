/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/06 17:32:15 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenisation.h"

int	ft_get_size_envtk(t_global *global, char *str, int *i, int *sz)
{
	int	idx;
	int	size;
	int	env_len;

	idx = *i;
	size = *sz;
	if (str[idx] == '$')
	{
		env_len = ft_env_len_bis(global, str + idx + 1);
		if (env_len == -1)
			return (-1);
		size += env_len;
		idx += ft_envname_len(str + idx + 1);
	}
	else
		size++;
	idx++;
	*i = idx;
	*sz = size;
	return (1);
}

int	ft_get_size_qtoken(t_global *global, char *str, int *idx, int *size)
{
	while (str[*idx] && is_in_set(str[*idx], "\"'"))
	{
		if (str[*idx] && str[*idx] == '"')
		{
			(*idx)++;
			while (str[*idx] && str[*idx] != '"')
			{
				if (ft_get_size_envtk(global, str, idx, size) == -1)
					return (-1);
			}
			(*idx)++;
		}
		if (str[*idx] && str[*idx] == '\'')
			*size += ft_skipquotes(str + (*idx), '\'') - 2;
		*idx += ft_skipquotes(str + (*idx), '\'');
	}
	return (1);
}

int	ft_size_token(t_global *global, char *str)
{
	int	idx;
	int	size;

	size = 0;
	idx = 0;
	while (str[idx] && is_in_set(str[idx], " 	"))
		idx++;
	while (str[idx] && !is_in_set(str[idx], " 	|"))
	{
		if (!ft_get_size_qtoken(global, str, &idx, &size))
			return (-1);
		while (str[idx] && !is_in_set(str[idx], "\"' 	|<>"))
		{
			if (ft_get_size_envtk(global, str, &idx, &size) == -1)
				return (-1);
		}
		while (str[idx] && is_in_set(str[idx], "<>"))
			idx += ft_redir_len(str + idx);
	}
	return (size);
}

int	skip_not_in_set(char *src, char *set)
{
	int	i;

	i = 0;
	while (src[i] && !is_in_set(src[i], set))
		i++;
	return (i);
}

t_command	*ft_token(char *line, t_global *global)
{
	t_command	*cmd;
	int			pos;

	cmd = ft_cmd_init();
	if (!cmd)
		return (perr(ERR_ALLOC), NULL);
	global->command = cmd;
	global->tmp = cmd;
	pos = 0;
	while (*line)
	{
		if (!ft_fillcmd(global, &line, &pos))
			return (NULL);
		if (global->tmp->next)
			global->tmp = global->tmp->next;
	}
	return (cmd);
}
