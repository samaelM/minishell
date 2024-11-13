/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execve_cmd.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:34:17 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/13 15:52:07 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	execve_absolute_path(t_global *g)
{
	if (execve(g->tmp->args[0], g->tmp->args, g->env) == -1)
	{
		if (access(g->tmp->args[0], F_OK) == 0)
		{
			if (access(g->tmp->args[0], X_OK) != 0)
				ft_perrorf("%s: Permission denied\n", g->tmp->args[0]);
			else
				ft_perrorf("%s: Is a directory\n", g->tmp->args[0]);
			ft_free_glob(g);
			exit(126);
		}
		else
			perror(g->tmp->args[0]);
		ft_free_glob(g);
		exit(127);
	}
}

char	**get_all_paths(char **env)
{
	while (*env)
	{
		if (ft_strnstr(*env, "PATH=", 5))
			break ;
		env++;
	}
	if (*env)
		return (ft_split(*env + 5, ':'));
	return (NULL);
}

char	*get_path(char **all_paths, char *cmd)
{
	int		i;
	char	*path;
	char	*tmp;

	i = 0;
	while (all_paths && cmd && all_paths[i])
	{
		tmp = ft_strjoin(all_paths[i], "/");
		if (!tmp)
			return (0);
		path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!path)
			return (0);
		if (access(path, X_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	ft_perrorf("%s: command not found\n", cmd);
	return (0);
}

void	execve_cmd_path(t_global *g)
{
	char	*path;
	char	**all_paths;

	all_paths = get_all_paths(g->env);
	path = get_path(all_paths, g->tmp->args[0]);
	if (!path)
	{
		free_tab(all_paths);
		ft_free_glob(g);
		exit(127);
	}
	if (execve(path, g->tmp->args, g->env) == -1)
	{
		perror("Execve");
		free_tab(all_paths);
		free(path);
		ft_free_glob(g);
		exit(1);
	}
}

void	execve_cmd(t_global *g)
{
	int	i;

	i = 0;
	while (g->tmp->args[0][i])
	{
		if (g->tmp->args[0][i] == '/')
			execve_absolute_path(g);
		i++;
	}
	execve_cmd_path(g);
}
