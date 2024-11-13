/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:52:13 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/13 19:47:22 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	dup_infile(t_global *g, int i)
{
	if (g->tmp->infile != -1)
	{
		dup2(g->tmp->infile, 0);
		// close(g->tmp->infile); //
	}
	else if (i != 0)
	{
		dup2(g->tmp->prev_fd, 0);
		close(g->tmp->prev_fd);
	}
}

void	dup_outfile(t_global *g)
{
	if (g->tmp->outfile != -1)
	{
		dup2(g->tmp->outfile, 1);
		// close(g->tmp->outfile); //
	}
	else if (g->tmp->next)
	{
		dup2(g->tmp->pipe[1], 1);
		// close(g->tmp->pipe[1]); //
	}
	// else //
	close(g->tmp->pipe[1]);
}

void	close_all_fd_child(t_global *g)
{
	t_command	*tmp;

	tmp = g->command;
	while (tmp)
	{
		// ft_perrorf("test (%s)\n", tmp->args[0]);
		// ft_putstr_fd(tmp->args[0], 2);
		if (tmp->infile != -1)
		{
			close(tmp->infile);
			// ft_putstr_fd("close!\n", 2);
		}
		if (tmp->outfile != -1)
		{
			close(tmp->outfile);
			// ft_putstr_fd("close outf!\n", 2);
		}
		tmp = tmp->next;
	}
}

int	exec_which_cmd_pipe(t_global *g, int i)
{
	if (check_is_cmd_is_ok(g) == 0)
	{
		dup_infile(g, i);
		dup_outfile(g);
		close_all_fd_child(g);
		if (ft_strcmp(g->tmp->args[0], "exit") == 0)
			return (ft_exit(g, 1));
		else if (ft_strcmp(g->tmp->args[0], "pwd") == 0)
			g->exit_value = ft_pwd();
		else if (ft_strcmp(g->tmp->args[0], "cd") == 0)
			g->exit_value = ft_cd(g);
		else if (ft_strcmp(g->tmp->args[0], "echo") == 0)
			g->exit_value = ft_echo(g->tmp);
		else if (ft_strcmp(g->tmp->args[0], "env") == 0)
			g->exit_value = ft_env(g);
		else if (ft_strcmp(g->tmp->args[0], "export") == 0)
			g->exit_value = ft_export(g);
		else if (ft_strcmp(g->tmp->args[0], "unset") == 0)
			g->exit_value = ft_unset(g);
		else
			execve_cmd(g);
	}
	ft_free_glob(g);
	exit(g->exit_value);
}

int	pipe_and_fork(t_global *g, int i)
{
	pid_t	pid;

	if (pipe(g->tmp->pipe) == -1)
		return (1);
	pid = fork();
	if (pid == -1)
		ft_perrorf("erreur fork");
	else if (pid == 0) // fils
	{
		close(g->tmp->pipe[0]);
		exec_which_cmd_pipe(g, i);
	}
	g->last_pid = pid;
	if (g->tmp->infile != -1)
		close(g->tmp->infile);
	if (g->tmp->outfile != -1)
		close(g->tmp->outfile);
	return (0);
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
