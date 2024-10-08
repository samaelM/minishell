/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:30:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/08 15:24:24 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void change_old_pwd(t_global *glo, char *geten)
{
	char *string;
	int is_line;
	
	string = malloc(sizeof(char) * (8 + ft_strlen(geten)));
	ft_strlcpy(string,"OLDPWD=", 8);
	ft_memcpy(string+7, geten, ft_strlen(geten));
	is_line = find_var_in_env(glo->env, "OLDPWD");
	if(is_line != -1)
		change_env_var(glo, string, is_line);
	free(string);
}

void change_pwd(t_global *glo, char *geten)
{
	char buf[PATH_MAX];
	char *string;
	char *next;
	int is_line;

	next = getcwd(buf, PATH_MAX);
	string = malloc(sizeof(char) * (5 + ft_strlen(next)));
	ft_strlcpy(string,"PWD=", 5);
	ft_memcpy(string+4, next, ft_strlen(next));
	is_line = find_var_in_env(glo->env, "PWD");
	if(is_line != -1)
		change_env_var(glo, string, is_line);
	free(string);
}

int ft_cd(t_global *glo)
{
	// tmp si fonctionne == tmp;
	char *tmp = ft_getenv(glo, "PWD");

// change_pwd(glo);

	
			
	char *home;
	if(glo->command->args[1] == NULL)
	{
		// printf("\n%s\n", ft_getenv(glob, "HOME"));
		home = ft_getenv(glo, "HOME"); // home no unset
		if(!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if(chdir(home))
		{
			printf("cd: %s\n", strerror(errno));
			return (1);
		}
		change_old_pwd(glo, tmp);
		change_pwd(glo);
		printf("pwd %s\n", ft_getenv(glo ,"PWD"));
		printf("old %s\n", ft_getenv(glo ,"OLDPWD"));
		return (0);
	}
	if(glo->command->args[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if(glo->command->args[1] && chdir(glo->command->args[1]))
	{
		printf("cd: %s: %s\n", glo->command->args[1], strerror(errno));
		return (1);
	}
	change_old_pwd(glo, tmp);
	change_pwd(glo);
	return (0);
}
