/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipe_cmds.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 18:52:13 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/11 17:39:37 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"



void	dup_infile(t_global *g, int i)
{
	if (g->command->infile != -1)
		dup2(g->command->infile, 0);
	else if (i != 0)
	{
		dup2(g->command->prev_fd, 0);
		close(g->command->prev_fd);
	}
}

void	dup_outfile(t_global *g)
{
	if (g->command->outfile != -1)
		dup2(g->command->outfile, 1);
	else if (g->command->next)
	{
		dup2(g->command->pipe[1], 1);
		close(g->command->pipe[1]);
	}
	else
		close(g->command->pipe[1]);
}

int	exec_which_cmd_pipe(t_global *g)
{
	if (g->command && g->command->args && g->command->args[0])
	{
		change_env_(g);
		if (ft_strcmp(g->command->args[0], "exit") == 0)
			g->exit_value = ft_exit(g);
		else if (ft_strcmp(g->command->args[0], "pwd") == 0)
			g->exit_value = ft_pwd();
		else if (ft_strcmp(g->command->args[0], "cd") == 0)
			g->exit_value = ft_cd(g);
		else if (ft_strcmp(g->command->args[0], "echo") == 0)
			g->exit_value = ft_echo(g->command);
		else if (ft_strcmp(g->command->args[0], "env") == 0)
			g->exit_value = ft_env(g);
		else if (ft_strcmp(g->command->args[0], "export") == 0)
			g->exit_value = ft_export(g);
		else if (ft_strcmp(g->command->args[0], "unset") == 0)
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

	pipe(g->command->pipe);
	pid = fork();
	if (pid == -1)
		ft_perrorf("erreur fork");
	else if (pid == 0) // fils
	{
		close(g->command->pipe[0]);
		dup_infile(g, i);
		dup_outfile(g);
		exec_which_cmd_pipe(g);
	}
	return (0);
}

void	exec_pipe_cmds(t_global *g)
{
	int	i;

	i = 0;
	g->tmp = g->command;
	while (g->command)
	{
		pipe_and_fork(g, i);
		i++;
		close(g->command->pipe[1]);
		if (g->command->next)
		{
			g->command->next->prev_fd = g->command->pipe[0];
			if (g->command->prev_fd != -1)
				close(g->command->prev_fd);
			g->command = g->command->next;
		}
		else
			break ;
	}
	close(g->command->pipe[0]);
	if (g->command->prev_fd != -1)
		close(g->command->prev_fd);
	ft_waitall(g);
}
