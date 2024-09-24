/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/04 20:28:12 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	absolute_path(t_global *glo)
{
	(void)glo;
	// if (execve(glo->command->cmd, glo->command->args, glo->env_list) == -1)
	{
		// perror(cmd[0]);
		// close_all_fd(pipex);
		// free(pipex.pipe);
		// free_all(cmd);
		// exit(1);
	}
}

void	exec_la_cmd(t_global *glo)
{
	int	i;

	i = 0;
	while (glo->command->cmd[i])
	{
		if (glo->command->cmd[i] == '/')
		{
			absolute_path(glo);
		}
		i++;
	}
	// cmd_path(cmd, pipex);
	printf("exe\n");
	return ;
}

int	execution(t_global *glo)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		printf("erreur fork");
	else if (pid == 0)
	{
		// if (glo->command->next)
		// 	printf("pipe\n");
		exec_la_cmd(glo);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
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
	if (glob->command->cmd)
	{
		char *var_ = malloc(sizeof(char) * (12 + ft_strlen(glob->command->cmd) + 2));
		ft_strlcpy(var_,"_=/usr/bin/", 12);
		ft_strlcpy(var_ + 12, glob->command->cmd, ft_strlen(glob->command->cmd));
		//ft_strlcat(var_, glob->command->cmd, ft_strlen(glob->command->cmd));
		change_env_var(glob, var_, find_var_in_env(glob->env, "_"));
		
		if (ft_strcmp(glob->command->cmd, "exit") == 0)
		{
			ft_exit(glob);
		}
		else if (ft_strcmp(glob->command->cmd, "pwd") == 0)
		{
			ft_pwd();
		}
		else if (ft_strcmp(glob->command->cmd, "cd") == 0)
		{
			ft_cd(glob->command);
		}
		else if (ft_strcmp(glob->command->cmd, "echo") == 0)
		{
			ft_echo(glob->command);
		}
		else if (ft_strcmp(glob->command->cmd, "env") == 0)
		{
			ft_env(glob);
		}
		else if (ft_strcmp(glob->command->cmd, "export") == 0)
		{
			ft_export(glob);
		}
		else if (ft_strcmp(glob->command->cmd, "unset") == 0)
		{
			ft_unset(glob);
		}
		else
		{
			execution(glob);
		}
	}
	return (0);
}
