/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:48:08 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/27 20:54:31 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// add
// modify
// delete

// pas de _


int change_env_var(t_list *env_list, char *var)
{
	char *buf = NULL;

	printf("%s\n", (char *)env_list->content);
	ft_bzero(env_list->content, ft_strlen(env_list->content));
	ft_strlcat(env_list->content, var, ft_strlen(var) + 1);
	if (ft_strncmp(var, "PWD=", 4) == 0)
		ft_strlcat(env_list->content, getcwd(buf, PATH_MAX), PATH_MAX + 1);
	// else
	// 	ft_strlcat(env_list->content, getcwd(buf, PATH_MAX), PATH_MAX + 1);
	printf("%s\n", (char *)env_list->content);
	return (0);
}

int add_env_var(t_list *env_list, char *var)
{
//	printf("%s\n", (char *)env_list->content);
	ft_lstadd_back(&env_list, ft_lstnew(var));
	//printf("%s\n", (char *)env_list->content);
	return (0);
}

// si tu touves avec strcmp, tu change
int ft_export(t_command *command, t_list *env_list)
{
	int i = 1;
	
	// if(command->args[1] == NULL)
	//	print export + var dans l'ordre ascii
	while(command->args[i])
	{
		t_list *tmp = find_var_in_env(env_list, command->args[i]);
		if(tmp != NULL)
			change_env_var(tmp, command->args[i]);
		else
		{
			printf("pas trouve la variable il faudra add\n");
			// sinon tu add nvlle var
			//add_env_var(tmp, command->args[i]);
		}
		i++;
	}
//	printf("c ici %i\n", find_env(command, env_list, "PWD="));
	return (0);
}
