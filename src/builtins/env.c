/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:59 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/04 18:43:21 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_env(t_global *glob)
{
	int i;
	
	i = 0;
	while(glob->env[i])
	{
		printf("%s\n", glob->env[i]);
		i++;
	}
	return (0);
}

char **create_our_env(char **envp)
{
	int i;
	char	**env_tab;

	i = 0;
	while(envp[i])
		i++;
	env_tab = malloc(sizeof(char *) * i + 1);
	if (!env_tab)
		return (NULL);
	i = 0;
	while (envp[i])
	{
		env_tab[i] = ft_strdup(envp[i]);
 		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}


// int ft_env(t_command *command, t_list *env_list)
// {
// 	(void)command;
// 	while (env_list)
// 	{
// 		printf("%s\n", (char *)env_list->content);
// 		env_list = env_list->next;
// 	}
// 	return (0);
// }

// t_list *create_our_env(char **envp)
// {
// 	t_list	*env_list = NULL;
// 	t_list *tmp;
	
// 	ft_lstadd_back(&env_list, ft_lstnew((void *)*envp));
// 	tmp = env_list;
// 	envp++;
// 	while (*envp)
// 	{
// 		ft_lstadd_back(&env_list, ft_lstnew((void *)*envp));
// 		env_list = env_list->next;
//  		envp++;
// 	}
// 	return (tmp);
// }