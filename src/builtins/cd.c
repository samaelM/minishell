/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/21 14:30:33 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 14:11:00 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getcwd(void)
{
	char	*cwd;

	cwd = malloc(PATH_MAX);
	if (!cwd)
	{
		ft_perrorf("change pwd variable: error with malloc\n");
		return (NULL);
	}
	if (getcwd(cwd, PATH_MAX) == NULL)
	{
		ft_perrorf("getcwd: cannot access parent directories\n");
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
	string = malloc(sizeof(char) * (5 + ft_strlen(cwd) + 1));
	if (!string)
	{
		free(cwd);
		ft_perrorf("cd: error with malloc\n");
		return (1);
	}
	ft_strlcpy(string, "PWD=", 5);
	ft_strlcat(string, cwd, 5 + ft_strlen(cwd));
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

	if (!cwd)
		return (1);
	string = malloc(sizeof(char) * (8 + ft_strlen(cwd) + 1));
	if (!string)
	{
		free(cwd);
		ft_perrorf("cd: error with malloc\n");
		return (1);
	}
	ft_strlcpy(string, "OLDPWD=", 8);
	ft_strlcat(string, cwd, 8 + ft_strlen(cwd));
	is_line = find_var_in_env(g->env, "OLDPWD");
	if (is_line != -1)
		change_env_var(g, string, is_line);
	else
		add_env_var(g, string);
	free(cwd);
	free(string);
	return (change_pwd(g));
}

int	cd_options(t_global *g, char *var, char *cwd)
{
	char	*path;

	path = ft_getenv(g->env, var);
	if (!path)
	{
		if (cwd)
			free(cwd);
		ft_perrorf("cd: %s not set\n", var);
		return (1);
	}
	if (chdir(path))
	{
		if (cwd)
			free(cwd);
		ft_perrorf("cd: %s: %s\n", path, strerror(errno));
		return (1);
	}
	if (ft_strcmp(var, "OLDPWD") == 0)
		ft_pwd();
	return (change_pwd_vars(g, cwd));
}

int	ft_cd(t_global *g)
{
	char	*cwd;

	if (g->tmp->args[1] && g->tmp->args[2])
	{
		ft_perrorf("cd: too many arguments\n");
		return (1);
	}
	cwd = ft_getcwd();
	if (g->tmp->args[1] == NULL)
		return (cd_options(g, "HOME", cwd));
	if (ft_strcmp(g->tmp->args[1], "-") == 0)
		return (cd_options(g, "OLDPWD", cwd));
	if (g->tmp->args[1] && chdir(g->tmp->args[1]))
	{
		if (cwd)
			free(cwd);
		ft_perrorf("cd: %s: %s\n", g->tmp->args[1], strerror(errno));
		return (1);
	}
	return (change_pwd_vars(g, cwd));
}
