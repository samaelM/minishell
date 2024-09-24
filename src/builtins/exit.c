/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:22:30 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/24 18:49:41 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int nb_args(char **args)
{
	int i = 0;
	while (args[i])
		i++;
	return (i);
}

int is_nb(char *cmd)
{
	int i = 0;

	while(cmd[i] == 32 || cmd[i] == '\0')
	{
		if(cmd[i] == '\0')
			return (1);
		i++;
	}
	if(cmd[i] == '+' || cmd[i] == '-')
		i++;
	while(ft_isdigit(cmd[i]))
		i++;
	while(cmd[i] == 32)
		i++;
	if(cmd[i] != '\0')
		return (1);
	return (0);
}

int is_nb_ok(char *cmd)
{
	int nb = ft_atoi(cmd);
	//printf("nb %i\n", nb);
	return (nb % 256);
}

int ft_exit(t_command *command)
{
	printf("exit\n");
	if(nb_args(command->args + 1) == 0)
	{
		free(command);
		exit(0);
		//exit(command->exit_value);
	}
	if(is_nb(command->args[1]))
	{	
		printf("exit: %s: numeric argument required\n", command->args[1]);
		free(command);
		exit(2);
	}
	if(is_nb(command->args[1]) == 0 && nb_args(command->args + 1) == 1)
	{
		free(command);
		exit(is_nb_ok(command->args[1]));
	}
	//if(is_nb(command->args[1]) == 0 && nb_args(command->args + 1) >= 2)
	else		
	{
		//command->exit_value = 1; pb de structure
		printf("exit: too many arguments\n");
	}
	return(0);
}	

// retirer espace a la fin
// que exit pas exitttt == parsing =) / guillemets a retirer
// exit n
// si chars apres exit ; exit et "numeric argument required"
// : too many arguments
//free(cmd);

