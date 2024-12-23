/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 19:12:25 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 15:36:34 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_getenv(char **env, char *var)
{
	int	line;
	int	i;

	i = 0;
	line = find_var_in_env(env, var);
	if (line == -1)
		return (NULL);
	while (env[line][i] && env[line][i] != '=')
		i++;
	return (env[line] + i + 1);
}

char	*ft_var_name(char *var)
{
	int		i;
	char	*new_line;

	i = 0;
	if (!var)
		return (NULL);
	while (var[i] && var[i] != '=')
		i++;
	new_line = malloc(sizeof(char) * (i + 1));
	if (!new_line)
	{
		ft_perrorf("env: error with malloc\n");
		return (NULL);
	}
	i = 0;
	while (var[i] && var[i] != '=')
	{
		new_line[i] = var[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

void	change_env_(t_global *g)
{
	char	*var_;
	int		line;

	var_ = malloc(sizeof(char) * (12 + ft_strlen(g->tmp->args[0])));
	if (!var_)
	{
		ft_perrorf("env: error with malloc\n");
		return ;
	}
	ft_strlcpy(var_, "_=/usr/bin/", 12);
	ft_strlcat(var_, g->tmp->args[0], 12 + ft_strlen(g->tmp->args[0]));
	line = find_var_in_env(g->env, "_");
	if (line != -1)
		change_env_var(g, var_, find_var_in_env(g->env, "_"));
	free(var_);
}

int	change_env_var(t_global *g, char *var, int line)
{
	char	*tmp;

	if (line == -1)
		return (1);
	tmp = g->env[line];
	g->env[line] = ft_strdup(var);
	if (!g->env[line])
	{
		ft_perrorf("export: error with malloc\n");
		g->env[line] = tmp;
		return (1);
	}
	free(tmp);
	return (0);
}

int	find_var_in_env(char **env, char *var)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if ((ft_strncmp(env[i], var, ft_strlen(var)) == 0)
			&& env[i][ft_strlen(var)] == '=')
			return (i);
		i++;
	}
	return (-1);
}
