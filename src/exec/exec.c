/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/30 15:19:26 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	execution(t_command *command, t_list *env_list)
{
	//	pid_t	pid;
	//	int		status;	
	(void)command;
	(void) env_list;
	// 	pid = fork();
	// 	if (pid == -1)
	//		printf("erreur fork");
	// 	else if (pid == 0)
	// 	{
	// 		if (ft_strncmp(cmd, "/bin/pwd", 8) == 0)
	// 		{
	// 			exec_cmd(cmd, envp);
	// 		}
	// 		return(0);
	// 	}
	// else
	// 	waitpid(pid, &status, 0);
	return (0);
}

int ft_exec(t_global *glob)
{
	if(glob->command->cmd)
	{
		if (ft_strncmp(glob->command->cmd, "exit", 4) == 0)
		{	
			ft_exit(glob);
		}
		else if(ft_strncmp(glob->command->cmd, "pwd", 3) == 0)
		{	
			ft_pwd();
		}
		else if(ft_strncmp(glob->command->cmd, "cd", 2) == 0)
		{
			ft_cd(glob->command);
		}
		else if(ft_strncmp(glob->command->cmd, "echo", 4) == 0)
		{
			ft_echo(glob->command);
		}
		else if (ft_strncmp(glob->command->cmd, "env", 3) == 0)
		{	
			ft_env(glob->command, glob->env_list);
		}
		else if(ft_strncmp(glob->command->cmd, "export", 6) == 0 )
		{
			ft_export(glob->command, glob->env_list);
		}
		else if(ft_strncmp(glob->command->cmd, "unset", 5) == 0 )
		{
			ft_unset(glob->command, glob->env_list);
		}
		else
		{
			execution(glob->command, glob->env_list);
		}
	}
	//free(command->cmd);
	// clear lst;
	// pb de commande pwddddddddd
	return (0);
}


