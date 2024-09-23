/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:30:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/23 17:36:40 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*
replicate the functions of the bash command cd
args:
return:
*/

int ft_cd(t_command *command)
{
	char *home;
	//ft_pwd();
	if(command->args == NULL)
	{
		home = getenv("HOME");
		if(!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if(chdir(home))
		{
			printf("cd: %s\n", strerror(errno));
			return (1);
		}
		// $PWD pas a jour		printf("%s\n", getenv("PWD"));
		return (0);
	}
	if(command->args[1])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if(command->args[0] && chdir(command->args[0]))
	{
		printf("cd: %s: %s\n", command->args[0], strerror(errno));
		return (1);
	}
	//ft_pwd();
	return (0);
}