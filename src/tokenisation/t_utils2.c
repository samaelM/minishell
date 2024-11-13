/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:30:35 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/13 18:49:52 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenisation.h"

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
		if (str[idx] && !is_in_set(str[idx], "<>"))
			nb_t++;
		while (str[idx] && !is_in_set(str[idx], "<> 	"))
		{
			idx += ft_skipquotes(str + idx, '"');
			idx += ft_skipquotes(str + idx, '\'');
			if (str[idx] && str[idx] == '|')
				return (nb_t);
			idx += skip_not_in_set(str + idx, "<>\"' 	|");
		}
	}
	return (nb_t);
}

int	ft_set_args(t_global *global, char **cmd, int *pos, int size)
{
	int		idx;
	char	**args;
	int		sizetk;

	args = global->tmp->args;
	idx = 0;
	while (idx < size)
	{
		sizetk = ft_size_token(global, *cmd);
		// printf("sztk: %d (%s)\n", sizetk, *cmd);
		if (sizetk == -1)
			return (0);
		args[idx] = ft_calloc(sizetk + 1, sizeof(char));
		if (!args[idx])
			return (perr(ERR_ALLOC), 0);
		// printf("ouioui:%s\n", *cmd);
		*pos = ft_get_arg(global, args[idx], *cmd);
		if (*pos == -1)
			return (0);
		*cmd = *cmd + *pos;
		// printf("avant redirlen:%s\n", *(cmd));
		while (**cmd && is_in_set(**cmd, "<>"))
			*cmd += ft_redir_len(*cmd);//-1?
		// printf("apres redirlen:%s\n", *(cmd));
		idx++;
	}
	args[idx] = 0;
	// printf("arg: %s\n", args);
	return (1);
}

t_command	*ft_cmd_init(void)
{
	t_command	*command;

	command = ft_calloc(1, sizeof(t_command));
	if (!command)
		return (NULL);
	command->infile = -1;
	command->outfile = -1;
	command->prev_fd = -1;
	return (command);
}

int	ft_fillcmd(t_global *global, char **line, int *pos)
{
	int			size;
	t_command	*cmd;

	cmd = global->tmp;
	size = ft_counttoken(*line);
	// printf("nbtk:%d (%s)\n", size, *line);
	cmd->args = ft_calloc((size + 1), sizeof(char *));
	if (!cmd->args)
		return (perr(ERR_ALLOC), 0);
	if (!ft_set_args(global, line, pos, size))
		return (0);
	while (**line && is_in_set(**line, " 	"))
		(*line)++;
	if (**line && is_in_set(**line, "<>"))
		*line += ft_redir_len(*line);
	// ft_printcmd(cmd);
	if (**line && **line == '|')
	{
		(*line)++;
		// printf("next cmd\n");
		cmd->next = ft_cmd_init();
		if (!cmd->next)
			return (perr(ERR_ALLOC), 0);
	}
	return (1);
}
