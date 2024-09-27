/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:46:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/27 19:03:41 by ahenault         ###   ########.fr       */
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

// pb trouve var plus courte
t_list *find_var_in_env(t_list *env_list, char *var)
{
	while (env_list)
	{
		if (ft_strncmp(env_list->content, var, ft_strlen(var)) == 0) 
		{	
			//unset_this_line(env_list);
			printf("%s\n", (char *)env_list->content);
			return (env_list);
		}
		env_list = env_list->next;
	}
	printf("pas trouve\n");
	return (NULL);
}

int ft_unset(t_command *command, t_list *env_list)
{
	int i = 1;
	
	while(command->args[i])
	{
		//printf("unset: %i\n"),
		t_list *tmp = find_var_in_env(env_list, command->args[i]);
		if(tmp != NULL)
			unset_this_line(tmp);
		i++;
	}
	return (0);
}
