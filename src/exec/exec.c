/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/31 14:46:30 by ahenault         ###   ########.fr       */
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

int	one_cmd(t_global *g, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("erreur fork");
	else if (pid == 0) // fils
	{
		close(g->command->pipe[0]);
		dup_infile(g, i);
		// printf("\033[0;93mcommande \033[0m\n");
		dup_outfile(g);
		exec_la_cmd(g);
	}
	else // pere
	{
		// if (WIFEXITED(status))
		// 	g->exit_value = WEXITSTATUS(status);
		if (g_sig)
			close(g->command->pipe[0]);
		g->exit_value = 128 + g_sig;
	}
	return (0);
}

int	execution(t_global *g)
{
	int	i;

	i = 0;
	while (g->command)
	{
		pipe(g->command->pipe);
		one_cmd(g, i);
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
	while (waitpid(0, NULL, 0) != -1)
		;
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

int	ft_exec(t_global *g)
{
	if (g->command && g->command->args && g->command->args[0])
	{
		change_env_(g);
		if (ft_strcmp(g->command->args[0], "exit") == 0)
		{
			g->exit_value = ft_exit(g);
		}
		else if (ft_strcmp(g->command->args[0], "pwd") == 0)
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
			execution(g);
		}
	}
	return (0);
}
