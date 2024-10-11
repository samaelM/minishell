/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:12:25 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/11 20:36:45 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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

void change_env_(t_global *glob) // = bash au debut
{
	char *var_;
	
	var_ = malloc(sizeof(char) * (12 + ft_strlen(glob->command->cmd) + 2));
	ft_strlcpy(var_,"_=/usr/bin/", 12);
	ft_memcpy(var_+11, glob->command->cmd, ft_strlen(glob->command->cmd));
	change_env_var(glob, var_, find_var_in_env(glob->env, "_"));
	//printf("%s\n", var_);
	free(var_);
}

char *ft_var_name(char *var)
{
	int i = 0;
	while(var[i] && var[i] != '=')
		i++;
	char *new_line = malloc(sizeof(char) * (i + 1));
	if(!new_line)
		return NULL;
	i = 0;
	while(var[i] && var[i] != '=')
	{
		new_line[i] = var[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
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

