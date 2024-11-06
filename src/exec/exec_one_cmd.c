/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_one_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 19:34:17 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/07 18:40:16 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	absolute_path(t_global *g)
{
	if (execve(g->command->args[0], g->command->args, g->env) == -1)
	{
		perror(g->command->args[0]);
		ft_free_glob(g);
		exit(1);
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
	ft_perrorf("command not found : %s\n", cmd);
	return (0);
}

void	cmd_path(t_global *g)
{
	char	*path;
	char	**all_paths;

	all_paths = get_all_paths(g->env);
	path = get_path(all_paths, g->command->args[0]);
	if (!path)
	{
		free_tab(all_paths);
		ft_free_glob(g);
		exit(1);
	}
	if (execve(path, g->command->args, g->env) == -1)
	{
		perror("Execve");
		free_tab(all_paths);
		free(path);
		ft_free_glob(g);
		exit(1);
	}
}

void	exec_la_cmd(t_global *g)
{
	int	i;

	i = 0;
	while (g->command->args[0][i])
	{
		if (g->command->args[0][i] == '/')
			absolute_path(g);
		i++;
	}
	cmd_path(g);
}
