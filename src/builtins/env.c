/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:59 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/11 16:22:30 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void change_env_(t_global *glob)
{
	char *var_;
	
	var_ = malloc(sizeof(char) * (12 + ft_strlen(glob->command->cmd) + 2));
	ft_strlcpy(var_,"_=/usr/bin/", 12);
	ft_memcpy(var_+11, glob->command->cmd, ft_strlen(glob->command->cmd));
	change_env_var(glob, var_, find_var_in_env(glob->env, "_"));
	//printf("%s\n", var_);
	free(var_);
}

// pb trouve var plus courte
int find_var_in_env(char **env, char *var)
{

	int i;
	
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, ft_strlen(var)) == 0) 
		{	
		//	printf("%s	trouve\n", env[i]);
			return (i);
		}
		i++;
	}
	return (-1);
}

char *ft_getenv(char **env, char *var)
{
	int line;
	int i;
	
	i = 0;
	line = find_var_in_env(env, var);
	if (line == -1)
		return (NULL);
	while(env[line][i] && env[line][i] != '=')
		i++;
	return (env[line] + i + 1);
}

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
	if(!envp) // gerer ca
	{
		printf("error no envp\n");
		// free
		exit(1);
	}
	while(envp[i])
		i++;
	env_tab = malloc(sizeof(char *) * (i + 1));
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