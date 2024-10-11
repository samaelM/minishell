/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:59 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/11 20:38:18 by ahenault         ###   ########.fr       */
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

char **create_env_i(void)
{
	char **env_tab;
	int i;
	
	env_tab = malloc(sizeof(char *) * 4);
	if (!env_tab)
	{
		printf("erreur malloc\n");
		return (NULL);
	}
	i = 0;
	while (i < 4)
	{
		env_tab[i] = "d";
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

char **create_our_env(char **envp)
{
	int i;
	char	**env_tab;

	if(envp[0] == NULL) // gerer ca
	{
		printf("error no envp\n");
		return (create_env_i());
	}
	i = 0;
	while(envp[i])
		i++;
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
	{
		printf("erreur malloc\n");
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		env_tab[i] = ft_strdup(envp[i]);
		if(!env_tab[i])
		{
			printf("erreur strdup\n");
			return (NULL);
		}
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}


