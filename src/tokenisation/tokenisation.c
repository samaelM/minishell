/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/10 16:22:24 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_get_size_qtoken(char *str, int *idx, int *size)
{
	while (str[*idx] && is_in_set(str[*idx], "\"'"))
	{
		if (str[*idx] && str[*idx] == '"')
		{
			(*idx)++;
			while (str[*idx] && str[*idx] != '"')
			{
				if (str[*idx] == '$')
				{
					*size += ft_env_len_bis(str + (*idx) + 1);
					*idx += ft_envname_len(str + (*idx) + 1);
				}
				else
					(*size)++;
				(*idx)++;
			}
			(*idx)++;
		}
		if (str[*idx] && str[*idx] == '\'')
			*size += ft_skipquotes(str + (*idx), '\'') - 2;
		*idx += ft_skipquotes(str + (*idx), '\'');
	}
}

int	ft_size_token(char *str)
{
	int	idx;
	int	size;

	size = 0;
	idx = 0;
	while (str[idx] && is_in_set(str[idx], " 	"))
		idx++;
	while (str[idx] && !is_in_set(str[idx], " 	|<>"))
	{
		ft_get_size_qtoken(str, &idx, &size);
		while (str[idx] && !is_in_set(str[idx], "\"' 	|<>"))
		{
			if (str[idx] == '$')
			{
				size += ft_env_len_bis(str + idx + 1);
				idx += ft_envname_len(str + idx + 1);
			}
			else
				size++;
			idx++;
		}
		while (str[idx] && is_in_set(str[idx], "<>"))
			idx += ft_redir_len(str + idx);
	}
	return (size);
}

int	ft_counttoken(char *str)
{
	int	idx;
	int	nb_t;

	idx = 0;
	nb_t = 0;
	while (str[idx])
	{
		while (str[idx] && is_in_set(str[idx], " 	"))
			idx++;
		if (is_in_set(str[idx], "<>"))
			idx += ft_redir_len(str + idx);
		if (str[idx] == '|')
			return (nb_t);
		if (str[idx])
			nb_t++;
		while (str[idx] && !is_in_set(str[idx], " 	"))
		{
			idx += ft_skipquotes(str + idx, '"');
			idx += ft_skipquotes(str + idx, '\'');
			if (str[idx] && str[idx] == '|')
				return (nb_t);
			while (str[idx] && !is_in_set(str[idx], "\"' 	|"))
				idx++;
		}
	}
	return (nb_t);
}

int	ft_set_args(char **args, char **cmd, int *pos, int size)
{
	int	idx;

	idx = 0;
	while (idx < size)
	{
		args[idx] = ft_calloc((ft_size_token(*cmd) + 1), sizeof(char));
		if (!args[idx])
			return (perr(ERR_ALLOC), 0);
		*pos = ft_get_arg(args[idx], *cmd);
		*cmd = *cmd + *pos;
		idx++;
	}
	args[idx] = 0;
	return (1);
}

t_command	*ft_token(char *line)
{
	t_command	*cmd;
	t_command	*tmp;
	int			pos;
	int			size;

	pos = 0;
	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	tmp = cmd;
	while (*line)
	{
		size = ft_counttoken(line);
		tmp->args = ft_calloc((size + 1), sizeof(char *));
		if (!tmp->args)
			return (perr(ERR_ALLOC), free(cmd), NULL);
		if (!ft_set_args(tmp->args, &line, &pos, size))
			return (ft_free_cmd(cmd), NULL);
		while (*line && is_in_set(*line, " 	"))
			line++;
		if (*line && is_in_set(*line, "<>"))
			line += ft_redir_len(line);
		if (*line && *line == '|')
			line++;
		if (*line)
		{
			tmp->next = ft_calloc(1, sizeof(t_command));
			if (!tmp->next)
				return (perr(ERR_ALLOC), ft_free_cmd(cmd), NULL);
			tmp = tmp->next;
		}
	}
	return (cmd);
}
