/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/07 19:09:16 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	check_is_cmd_is_ok(t_global *g)
{
	if (g->command && g->command->args && g->command->args[0])
	{
		change_env_(g);
		if (g->command->infile != -2 && g->command->outfile != -2)
			return (0);
	}
	return (1);
}

int	close_if_error(t_global *g)
{
	if (g->command->infile != -1)
	{
		if (dup2(g->command->stdin_copy, 0) == -1)
		{
			close(g->command->stdin_copy);
			if (g->command->outfile != -1 && g->command->stdout_copy != -1)
				close(g->command->stdout_copy);
			ft_free_glob(g);
			exit(1);
		}
		close(g->command->stdin_copy);
	}
	if (g->command->stdout_copy != -1)
		close(g->command->stdout_copy);
	return (1);
}

int	dup_infile_and_outfile(t_global *g)
{
	if (g->command->infile != -1)
	{
		g->command->stdin_copy = dup(0);
		if (g->command->stdin_copy == -1)
			return (1);
		if (dup2(g->command->infile, 0) == -1)
		{
			close(g->command->stdin_copy);
			return (1);
		}
	}
	if (g->command->outfile != -1)
	{
		g->command->stdout_copy = dup(1);
		if (g->command->stdout_copy == -1)
			return (close_if_error(g));
		if (dup2(g->command->outfile, 1) == -1)
			return (close_if_error(g));
	}
	return (0);
}

int	fork_execve(t_global *g)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perrorf("erreur fork");
	else if (pid == 0) // fils
	{
		if (g->command->infile != -1)
		{
			close(g->command->stdin_copy);
			close(g->command->infile);
		}
		if (g->command->outfile != -1)
		{
			close(g->command->stdout_copy);
			close(g->command->outfile);
		}
		exec_la_cmd(g);
	}
	ft_waitall(g);
	return (0);
}

void	exec_which_cmd(t_global *g)
{
	if (ft_strcmp(g->command->args[0], "pwd") == 0)
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
		fork_execve(g);
}

void	close_fd(t_global *g)
{
	if (g->command->infile != -1)
	{
		if (dup2(g->command->stdin_copy, 0) == -1)
		{
			close(g->command->stdin_copy);
			if (g->command->outfile != -1)
				close(g->command->stdout_copy);
			ft_free_glob(g);
			exit(1);
		}
		close(g->command->stdin_copy);
	}
	if (g->command->outfile != -1)
	{
		if (dup2(g->command->stdout_copy, 1) == -1)
		{
			close(g->command->stdout_copy);
			ft_free_glob(g);
			exit(1);
		}
		close(g->command->stdout_copy);
	}
}

int	exec_one_cmd(t_global *g)
{
	if (check_is_cmd_is_ok(g) == 1)
		return (1);
	if (ft_strcmp(g->command->args[0], "exit") == 0)
	{
		g->exit_value = ft_exit(g);
		return (1);
	}
	if (dup_infile_and_outfile(g) == 1)
	{
		g->exit_value = 1;
		ft_perrorf("erreur dup\n", 2);
		return (1);
	}
	exec_which_cmd(g);
	close_fd(g);
	return (0);
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
