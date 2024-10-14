/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/14 17:05:05 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_get_size_qtoken(t_global *global, char *str, int *idx, int *size)
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
					*size += ft_env_len_bis(global, str + (*idx) + 1);
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

int	ft_size_token(t_global *global, char *str)
{
	int	idx;
	int	size;

	size = 0;
	idx = 0;
	while (str[idx] && is_in_set(str[idx], " 	"))
		idx++;
	while (str[idx] && !is_in_set(str[idx], " 	|<>"))
	{
		ft_get_size_qtoken(global, str, &idx, &size);
		while (str[idx] && !is_in_set(str[idx], "\"' 	|<>"))
		{
			if (str[idx] == '$')
			{
				size += ft_env_len_bis(global, str + idx + 1);
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

int	ft_set_args(t_global *global, char **cmd, int *pos, int size)
{
	int		idx;
	char	**args;

	args = global->tmp->args;
	idx = 0;
	while (idx < size)
	{
		// printf("size=%d\n", ft_size_token(global, *cmd) + 1);
		args[idx] = ft_calloc((ft_size_token(global, *cmd) + 1), sizeof(char));
		if (!args[idx])
			return (perr(ERR_ALLOC), 0);
		*pos = ft_get_arg(global, args[idx], *cmd);
		*cmd = *cmd + *pos;
		idx++;
	}
	args[idx] = 0;
	return (1);
}

int	ft_fillcmd(t_global *global, char **line, int *pos)
{
	int			size;
	t_command	*cmd;

	cmd = global->tmp;
	size = ft_counttoken(*line);
	cmd->args = ft_calloc((size + 1), sizeof(char *));
	if (!cmd->args)
		return (0);
	if (!ft_set_args(global, line, pos, size))
		return (0);
	while (**line && is_in_set(**line, " 	"))
		(*line)++;
	if (**line && is_in_set(**line, "<>"))
		*line += ft_redir_len(*line);
	if (**line && **line == '|')
		(*line)++;
	if (**line)
	{
		cmd->next = ft_calloc(1, sizeof(t_command));
		if (!cmd->next)
			return (0);
	}
	return (1);
}

t_command	*ft_token(char *line, t_global *global)
{
	t_command	*cmd;
	int			pos;

	cmd = ft_calloc(1, sizeof(t_command));
	if (!cmd)
		return (NULL);
	global->command = cmd;
	global->tmp = cmd;
	pos = 0;
	while (*line)
	{
		if (!ft_fillcmd(global, &line, &pos))
			return (perr(ERR_ALLOC), ft_free_cmd(cmd), NULL);
		if (global->tmp->next)
			global->tmp = global->tmp->next;
	}
	if (cmd->args)
		cmd->cmd = cmd->args[0];
	return (cmd);
}

// sans compter readline
// mc = 1
// cm = n + 2
// pc = n + 2 + 2p + 2e + r + M
