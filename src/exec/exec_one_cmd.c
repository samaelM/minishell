/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/11 15:57:43 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/11 17:31:14 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

int	close_fd_if_error(t_global *g)
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
			return (close_fd_if_error(g));
		if (dup2(g->command->outfile, 1) == -1)
			return (close_fd_if_error(g));
	}
	return (0);
}

void	fork_and_execve(t_global *g)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		ft_perrorf("erreur fork");
	else if (pid == 0)
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
		execve_cmd(g);
	}
	ft_waitall(g);
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
		fork_and_execve(g);
}

int	exec_one_cmd(t_global *g)
{
	if (check_is_cmd_is_ok(g) == 1)
		return (1);
	if (ft_strcmp(g->command->args[0], "exit") == 0)
		return (ft_exit(g));
	if (dup_infile_and_outfile(g) == 1)
	{
		ft_perrorf("erreur dup\n", 2);
		return (1);
	}
	exec_which_cmd(g);
	close_fd(g);
	return (0);
}
