/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:48:08 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 15:18:05 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_env_var(t_global *g, char *var)
{
	char	**tab;
	int		i;

	i = 0;
	while (g->env[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 2));
	if (!tab)
		return (1);
	i = 0;
	while (g->env[i])
	{
		tab[i] = ft_strdup(g->env[i]);
		if (!tab[i])
		{
			free_tab(tab);
			ft_perrorf("export: error with malloc\n");
			return (1);
		}
		i++;
	}
	tab[i] = ft_strdup(var);
	if (!tab[i])
	{
		free_tab(tab);
		ft_perrorf("export: error with malloc\n");
		return (1);
	}
	tab[i + 1] = NULL;
	free_tab(g->env);
	g->env = tab;
	return (0);
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

int	parse_export(char *var, int *return_value)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) || var[i] == '_')
	{
		while (var[i])
		{
			if (var[i] == '=')
				return (0);
			if (ft_isalnum(var[i]) == 0 && var[i] != '_')
				break ;
			i++;
		}
	}
	if (var[i] != '\0')
	{
		ft_perrorf("export: `%s': not a valid identifier\n", var);
		*return_value = 1;
	}
	return (1);
}

int	print_export(t_global *g)
{
	int		i;
	char	*var_name;
	char	*var_content;

	i = 0;
	while (g->env[i])
	{
		if (ft_strncmp(g->env[i], "_", 1) != 0)
		{
			var_name = ft_var_name(g->env[i]);
			if (!var_name)
				return (1);
			var_content = ft_getenv(g->env, var_name);
			if (!var_content)
			{
				free(var_name);
				return (1);
			}
			ft_printf("export %s=\"%s\"\n", var_name, var_content);
			free(var_name);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_global *g)
{
	int		i;
	char	*var_name;
	int		return_value;
	int		line;

	i = 0;
	return_value = 0;
	if (g->tmp->args[1] == NULL)
		return (print_export(g));
	while (g->tmp->args[++i])
	{
		if (parse_export(g->tmp->args[i], &return_value) == 0)
		{
			var_name = ft_var_name(g->tmp->args[i]);
			if (!var_name)
				return (1);
			line = find_var_in_env(g->env, var_name);
			free(var_name);
			if (line == -1 && add_env_var(g, g->tmp->args[i]) == 1)
				return (1);
			if (line != -1 && change_env_var(g, g->tmp->args[i], line) == 1)
				return (1);
		}
	}
	return (return_value);
}
