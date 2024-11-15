/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 16:21:09 by ahenault         ###   ########.fr       */
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
		if (g_sig != 0)
		{
			g->exit_value = 128 + g_sig;
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

int	exec_one_cmd(t_global *g)
{
	if (check_is_cmd_is_ok(g, -1) == 1)
		return (1);
	if (ft_strcmp(g->command->args[0], "exit") == 0)
		return (ft_exit(g, 0));
	if (dup_infile_and_outfile(g) == 1)
	{
		ft_perrorf("exec: error with dup\n");
		g->exit_value = 1;
		return (1);
	}
	exec_which_cmd(g);
	close_fd(g);
	return (g->exit_value);
}

void	exec_pipe_cmds(t_global *g)
{
	int	i;

	i = 0;
	g->tmp = g->command;
	while (g->tmp)
	{
		pipe_and_fork(g, i);
		i++;
		close(g->tmp->pipe[1]);
		if (g->tmp->next)
		{
			g->tmp->next->prev_fd = g->tmp->pipe[0];
			if (g->tmp->prev_fd != -1)
				close(g->tmp->prev_fd);
			g->tmp = g->tmp->next;
		}
		else
			break ;
	}
	close(g->tmp->pipe[0]);
	if (g->tmp->prev_fd != -1)
		close(g->tmp->prev_fd);
	ft_waitall(g);
}

int	ft_exec(t_global *g)
{
	g_sig = 0;
	if (g->command->next == NULL)
		return (exec_one_cmd(g));
	exec_pipe_cmds(g);
	return (0);
}
