/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:59 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/27 20:58:37 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_env(t_command *command, t_list *env_list)
{
	(void)command;
	while (env_list)
	{
		printf("%s\n", (char *)env_list->content);
		env_list = env_list->next;
	}
	return (0);
}

t_list *create_our_env(char **envp)
{
	t_list	*env_list = NULL;
	t_list *tmp;
	
	ft_lstadd_back(&env_list, ft_lstnew((void *)*envp));
	tmp = env_list;
	envp++;
	while (*envp)
	{
		ft_lstadd_back(&env_list, ft_lstnew((void *)*envp));
		env_list = env_list->next;
 		envp++;
	}
	return (tmp);
}
