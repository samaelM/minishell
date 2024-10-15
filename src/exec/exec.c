/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/15 13:13:55 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execution(t_global *g)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("erreur fork");
	else if (pid == 0)
	{
		// if (g->command->next)
		// 	printf("pipe\n");
		exec_la_cmd(g);
		exit(0);
	}
	else
	{
		waitpid(pid, &status, 0);
		g->exit_value = status;
		if (g_sig)
			g->exit_value = 128 + g_sig;
	}
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

int	ft_exec(t_global *glob)
{
	if (glob->command && glob->command->cmd)
	{
	//	change_env_(glob);
		if (ft_strcmp(glob->command->cmd, "exit") == 0)
		{
			glob->exit_value = ft_exit(glob);
		}
		else if (ft_strcmp(glob->command->cmd, "pwd") == 0)
		{
			glob->exit_value = ft_pwd();
		}
		else if (ft_strcmp(glob->command->cmd, "cd") == 0)
		{
			glob->exit_value = ft_cd(glob);
		}
		else if (ft_strcmp(glob->command->cmd, "echo") == 0)
		{
			glob->exit_value = ft_echo(glob->command);
		}
		else if (ft_strcmp(glob->command->cmd, "env") == 0)
		{
			glob->exit_value = ft_env(glob);
		}
		else if (ft_strcmp(glob->command->cmd, "export") == 0)
		{
			glob->exit_value = ft_export(glob);
		}
		else if (ft_strcmp(glob->command->cmd, "unset") == 0)
		{
			glob->exit_value = ft_unset(glob);
		}
		// else
		// {
		// 	execution(glob);
		// }
	}
	return (0);
}
