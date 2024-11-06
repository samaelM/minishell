/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/06 19:50:52 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	exec_one_cmd(t_global *g)
{
	pid_t	pid;
	int		fd_stdin;
	int		fd_stdout;

	if (g->command && g->command->args && g->command->args[0])
	{
		if (g->command->infile == -2 || g->command->outfile == -2)
		{
			g->exit_value = 2;
			return (g->exit_value);
		}
		change_env_(g);
		if (ft_strcmp(g->command->args[0], "exit") == 0)
		{
			g->exit_value = ft_exit(g);
		}
		fd_stdin = dup(0);
		fd_stdout = dup(1);
		if (g->command->infile != -1)
			dup2(g->command->infile, 0);
		if (g->command->outfile != -1)
			dup2(g->command->outfile, 1);
		if (ft_strcmp(g->command->args[0], "pwd") == 0)
		{
			g->exit_value = ft_pwd();
		}
		else if (ft_strcmp(g->command->args[0], "cd") == 0)
		{
			g->exit_value = ft_cd(g);
		}
		else if (ft_strcmp(g->command->args[0], "echo") == 0)
		{
			g->exit_value = ft_echo(g->command);
		}
		else if (ft_strcmp(g->command->args[0], "env") == 0)
		{
			g->exit_value = ft_env(g);
		}
		else if (ft_strcmp(g->command->args[0], "export") == 0)
		{
			g->exit_value = ft_export(g);
		}
		else if (ft_strcmp(g->command->args[0], "unset") == 0)
		{
			g->exit_value = ft_unset(g);
		}
		else
		{
			pid = fork();
			if (pid == -1)
				ft_perrorf("erreur fork");
			else if (pid == 0) // fils
			{
				if (g->command->infile > 0)
					close(g->command->infile);
				if (g->command->outfile > 0)
					close(g->command->outfile);
				close(fd_stdin);
				close(fd_stdout);
				exec_la_cmd(g);
			}
			ft_waitall(g);
		}
		if (g->command->infile != -1)
			dup2(fd_stdin, 0);
		if (g->command->outfile != -1)
			dup2(fd_stdout, 1);
		close(fd_stdin);
		close(fd_stdout);
	}
	return (g->exit_value);
}

int	ft_exec(t_global *g)
{
	int	i;

	i = 0;
	if (g->command->next == NULL)
		return (exec_one_cmd(g));
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
	return (0);
}
