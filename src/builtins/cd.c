/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:30:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/14 19:32:18 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	change_pwd(t_global *glo)
{
	char	buf[PATH_MAX];
	char	*string;
	int		is_line;

	if (getcwd(buf, PATH_MAX) == NULL)
	{
		printf("erreur getcwd qd change var\n");
		return (1);
	}
	string = malloc(sizeof(char) * (5 + ft_strlen(buf)));
	if (!string)
	{
		printf("erreur malloc qd change var\n");
		return (1);
	}
	ft_strlcpy(string, "PWD=", 5);
	ft_memcpy(string + 4, buf, ft_strlen(buf) + 1);
	is_line = find_var_in_env(glo->env, "PWD");
	if (is_line != -1)
		change_env_var(glo, string, is_line);
	free(string);
	return (0);
}

int	change_pwd_vars(t_global *glo)
{
	char	*string;
	char	*content;
	int		is_line;

	content = ft_getenv(glo->env, "PWD");
	string = malloc(sizeof(char) * (8 + ft_strlen(content)));
	if (!string)
	{
		printf("erreur malloc qd change var\n");
		return (1);
	}
	ft_strlcpy(string, "OLDPWD=", 8);
	if (content)
		ft_memcpy(string + 7, content, ft_strlen(content) + 1);
	is_line = find_var_in_env(glo->env, "OLDPWD");
	if (is_line != -1)
		change_env_var(glo, string, is_line);
	free(string);
	return (change_pwd(glo));
}

int	ft_cd(t_global *glo)
{
	char	*home;

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
		return (change_pwd_vars(glo));
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
	return (change_pwd_vars(glo));
}
