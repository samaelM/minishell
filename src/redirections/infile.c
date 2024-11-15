/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:29:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 15:07:17 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_infile(t_global *global, char *line)
{
	char		*name;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->infile > 1)
		close(cmd->infile);
	name = ft_get_file_name(global, line);
	if (!name)
		return (-1);
	cmd->infile = open(name, O_RDONLY);
	if (cmd->infile == -1)
	{
		cmd->infile = -2;
		global->exit_value = 1;
		perror(name);
		free(name);
		return (-1);
	}
	free(name);
	return (1);
}

// malloc sensitive
int	ft_heredoc(t_global *global, char *line)
{
	char	*lim;
	int		fd[2];
	int		in_quote;

	in_quote = 0;
	lim = ft_getlim(global, line, &in_quote);
	if (!lim)
		return (perr("pas de lim\n"), -1);
	if (pipe(fd) == -1)
		return (free(lim), -1);
	if (in_quote)
		return (ft_hd_quote(global, fd, lim));
	return (ft_hd_nquote(global, fd, lim));
}
