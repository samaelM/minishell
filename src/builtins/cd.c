/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:30:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/15 16:54:48 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getcwd(void)
{
	char	*buf;
	char	s[PATH_MAX];

	if (getcwd(s, PATH_MAX) == NULL)
	{
		printf("erreur getcwd qd change var\n");
		return (NULL);
	}
	buf = s;
	return (buf);
}

int	change_pwd(t_global *glo)
{
	char	*buf;
	char	*string;
	int		is_line;

	buf = ft_getcwd();
	string = malloc(sizeof(char) * (5 + ft_strlen(buf)));
	if (!string)
	{
		printf("erreur malloc qd change var\n");
		return (1);
	}
	ft_strlcpy(string, "PWD=", 5);
	ft_strlcat(string, buf, (5 + ft_strlen(buf)));
	// ft_memcpy(string + 4, buf, ft_strlen(buf) + 1);
	is_line = find_var_in_env(glo->env, "PWD");
	if (is_line != -1)
		change_env_var(glo, string, is_line);
	else
		add_env_var(glo, string);
	free(string);
	return (0);
}

int	change_pwd_vars(t_global *glo, char *content)
{
	char	*string;
	int		is_line;

	string = malloc(sizeof(char) * (8 + ft_strlen(content)));
	if (!string)
	{
		printf("erreur malloc qd change var\n");
		return (1);
	}
	ft_strlcpy(string, "OLDPWD=", 8);
	ft_strlcat(string, content, 8 + ft_strlen(content));
	//	ft_memcpy(string + 7, content, ft_strlen(content) + 1);
	is_line = find_var_in_env(glo->env, "OLDPWD");
	if (is_line != -1)
		change_env_var(glo, string, is_line);
	else
		add_env_var(glo, string);
	free(string);
	return (change_pwd(glo));
}

int	ft_cd(t_global *glo)
{
	char	*home;
	char	*tmp;

	tmp = ft_getcwd();
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
		return (change_pwd_vars(glo, tmp));
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
	return (change_pwd_vars(glo, tmp));
}
