/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:30:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/15 21:09:59 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (!cwd)
		return (NULL);
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		printf("erreur getcwd qd change var\n");
		return (NULL);
	}
	return (cwd);
}

int	change_pwd(t_global *glo)
{
	char	*cwd;
	char	*string;
	int		is_line;

	cwd = ft_getcwd();
	if (!cwd)
		return (1);
	string = malloc(sizeof(char) * (ft_strlen("PWD=\0") + ft_strlen(cwd) + 1));
	if (!string)
	{
		printf("erreur malloc qd change var\n");
		return (1);
	}
	ft_strlcpy(string, "PWD=", 5);
	ft_strlcat(string, cwd, (5 + ft_strlen(cwd)));
	// ft_memcpy(string + 4, buf, ft_strlen(buf) + 1);
	is_line = find_var_in_env(glo->env, "PWD");
	if (is_line != -1)
		change_env_var(glo, string, is_line);
	else
		add_env_var(glo, string);
	free(string);
	free(cwd);
	return (0);
}

int	change_pwd_vars(t_global *glo, char *cwd)
{
	char	*string;
	int		is_line;

	string = malloc(sizeof(char) * (8 + ft_strlen(cwd) + 1));
	if (!string)
	{
		printf("erreur malloc qd change var\n");
		return (1);
	}
	ft_strlcpy(string, "OLDPWD=", 9);
	ft_strlcat(string, cwd, 9 + ft_strlen(cwd));
	//	ft_memcpy(string + 7, cwd, ft_strlen(cwd) + 1);
	is_line = find_var_in_env(glo->env, "OLDPWD");
	if (is_line != -1)
		change_env_var(glo, string, is_line);
	else
		add_env_var(glo, string);
	free(string);
	free(cwd);
	return (change_pwd(glo));
}

int	ft_cd(t_global *glo)
{
	char	*home;
	char	*cwd;

	cwd = ft_getcwd();
	if (!cwd)
		return (1);
	if (glo->command->args[1] == NULL)
	{
		home = ft_getenv(glo->env, "HOME");
		if (!home)
		{
			printf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(home))
		{
			printf("cd: %s\n", strerror(errno));
			return (1);
		}
		return (change_pwd_vars(glo, cwd));
	}
	if (glo->command->args[2])
	{
		printf("cd: too many arguments\n");
		return (1);
	}
	if (glo->command->args[1] && chdir(glo->command->args[1]))
	{
		printf("cd: %s: %s\n", glo->command->args[1], strerror(errno));
		return (1);
	}
	return (change_pwd_vars(glo, cwd));
}
