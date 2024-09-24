/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/24 18:54:04 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_exec(t_command *command, char **envp)
{
	//	pid_t	pid;
	//	int		status;	
	// command not found : exit, pwd, env, cd, echo, export, unset
	// command found : 
	
	if(command->cmd)
	{
		if (ft_strncmp(command->cmd, "exit", 4) == 0)
		{	
			ft_exit(command);
		}
		else if(ft_strncmp(command->cmd, "pwd", 3) == 0)
		{	
			ft_pwd();
		}
		else if(ft_strncmp(command->cmd, "cd", 2) == 0)
		{
			ft_cd(command);
		}
		else if(ft_strncmp(command->cmd, "echo", 4) == 0)
		{
			ft_echo(command);
		}
		else if (ft_strncmp(command->cmd, "env", 3) == 0)
		{	
			ft_env(command, envp);
		}
		
	// else if(ft_strncmp(command->cmd, "export", 6) == 0 )
	// {
	// 	ft_export(command->cmd);
	// }
	// else if(ft_strncmp(command->cmd, "unset", 5) == 0 )
	// {
	// 	ft_unset(command->cmd);
	// }
	//else if(*command->cmd) // espaces
	{
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
	}}
	//free(command->cmd);
	return (0);
}