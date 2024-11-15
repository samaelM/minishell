/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 15:22:46 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_waitall(t_global *g)
{
	int	pid;
	int	exit_status;

	while (42)
	{
		pid = wait(&exit_status);
		if (pid == g->last_pid)
		{
			if (WIFEXITED(exit_status))
				g->exit_value = WEXITSTATUS(exit_status);
		}
		// if (!WIFEXITED(exit_status))
		if (g_sig != 0)
		{
			g->exit_value = 128 + g_sig;
			// printf("%i\n", g->exit_value);
		}
		if (pid == -1)
			break ;
	}
}

int	check_is_cmd_is_ok(t_global *g, int i)
{
	if (g->tmp && g->tmp->args && g->tmp->args[0])
	{
		change_env_(g);
		if (g->tmp->infile != -2 && g->tmp->outfile != -2)
			return (0);
	}
	if (i != -1)
	{
		close_all_fd_child(g);
		if (i != 0)
			close(g->tmp->prev_fd);
		close(g->tmp->pipe[1]);
	}
	return (1);
}

int	ft_exec(t_global *g)
{
	g_sig = 0;
	if (g->command->next == NULL)
		return (exec_one_cmd(g));
	exec_pipe_cmds(g);
	return (0);
}
