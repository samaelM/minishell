/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:48:08 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/26 19:07:04 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// add
// modify
// delete

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

int find_env(t_command *command, t_list *env_list, char *var)
{
	(void)command;
	while (env_list)
	{
		if (ft_strncmp(env_list->content, var, 4) == 0)
		{	
			change_env_var(env_list, var);
			return (2);
		}
		env_list = env_list->next;
	}
	return (0);
}

int ft_export(t_command *command, t_list *env_list)
{
	(void)command;
	// si tu touves avec strcmp, tu change
	// sinon tu add nvlle var

	find_var_in_env(command, env_list, command->args[1]);
//	printf("c ici %i\n", find_env(command, env_list, "PWD="));
	return (0);
}
