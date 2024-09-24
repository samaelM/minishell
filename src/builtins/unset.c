/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:46:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/26 19:07:07 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int unset_this_line(t_list *env_list)
{
	//printf("%s\n", (char *)env_list->content);
//	t_list *tmp;

//	tmp = env_list->next;
	env_list->content = env_list->next->content;
	env_list->next = env_list->next->next;
//	free(tmp);
	//printf("%s\n", (char *)env_list->content);
	// malloc element rejete 
	return (0);
}

t_list *find_var_in_env(t_command *command, t_list *env_list, char *var)
{
	(void)command;
	while (env_list)
	{
		if (ft_strncmp(env_list->content, var, 4) == 0)
		{	
			//unset_this_line(env_list);
			return (env_list);
		}
		env_list = env_list->next;
	}
	return (NULL);
}

int ft_unset(t_command *command, t_list *env_list)
{
	(void)command;
	(void)env_list;
	int i = 1;
	
	while(command->args[i])
	//if(command->args[1])
	{
		//printf("unset: %i\n"),
		unset_this_line(find_var_in_env(command, env_list, command->args[i]));
		i++;
	}
	//ft_env(command, env_list);
	return (0);
}