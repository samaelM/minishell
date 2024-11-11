/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:30:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/11 20:06:07 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (!cwd)
	{
		ft_perrorf("erreur malloc\n");
		return (NULL);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_perrorf("erreur getcwd qd change var\n");
		free(cwd);
		return (NULL);
	}
	return (cwd);
}

int	change_pwd(t_global *g)
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
		ft_perrorf("erreur malloc qd change var\n");
		free(cwd);
		return (1);
	}
	ft_strlcpy(string, "PWD=", 5);
	ft_strlcat(string, cwd, (5 + ft_strlen(cwd)));
	is_line = find_var_in_env(g->env, "PWD");
	if (is_line != -1)
		change_env_var(g, string, is_line);
	else
		add_env_var(g, string);
	free(string);
	free(cwd);
	return (0);
}

int	change_pwd_vars(t_global *g, char *cwd)
{
	char	*string;
	int		is_line;

	string = malloc(sizeof(char) * (8 + ft_strlen(cwd) + 1));
	if (!string)
	{
		ft_perrorf("erreur malloc qd change var\n");
		free(cwd);
		return (1);
	}
	ft_strlcpy(string, "OLDPWD=", 9);
	ft_strlcat(string, cwd, 9 + ft_strlen(cwd));
	is_line = find_var_in_env(g->env, "OLDPWD");
	if (is_line != -1)
		change_env_var(g, string, is_line);
	else
		add_env_var(g, string);
	free(cwd);
	free(string);
	return (change_pwd(g));
}

int	ft_cd(t_global *g)
{
	char	*home;
	char	*cwd;

	cwd = ft_getcwd();
	if (!cwd)
		return (1);
	if (g->tmp->args[1] == NULL)
	{
		home = ft_getenv(g->env, "HOME");
		if (!home)
		{
			free(cwd);
			ft_perrorf("cd: HOME not set\n");
			return (1);
		}
		if (chdir(home))
		{
			free(cwd);
			ft_perrorf("cd: %s: %s\n", home, strerror(errno));
			return (1);
		}
		return (change_pwd_vars(g, cwd));
	}
	if (g->tmp->args[2])
	{
		free(cwd);
		ft_perrorf("cd: too many arguments\n");
		return (1);
	}
	if (g->tmp->args[1] && chdir(g->tmp->args[1]))
	{
		free(cwd);
		ft_perrorf("cd: %s: %s\n", g->tmp->args[1], strerror(errno));
		return (1);
	}
	return (change_pwd_vars(g, cwd));
}
