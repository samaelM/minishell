/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:48:08 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/18 20:18:33 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	add_env_var(t_global *glo, char *var)
{
	char	**tab;
	int		i;

	i = 0;
	while (glo->env[i])
		i++;
	tab = malloc(sizeof(char *) * (i + 2));
	if (!tab)
		return (1);
	i = 0;
	while (glo->env[i])
	{
		tab[i] = ft_strdup(glo->env[i]);
		if (!tab[i])
		{
			free_tab(tab);
			return (1);
		}
		i++;
	}
	tab[i] = ft_strdup(var);
	if (!tab[i])
	{
		free_tab(tab);
		return (1);
	}
	tab[i + 1] = NULL;
	free_tab(glo->env);
	glo->env = tab;
	return (0);
}

int	change_env_var(t_global *glo, char *var, int line)
{
	char	*tmp;

	tmp = glo->env[line];
	glo->env[line] = ft_strdup(var);
	if (!glo->env[line])
	{
		printf("export: erreur strdup\n");
		glo->env[line] = tmp;
		return (1);
	}
	free(tmp);
	return (0);
}

int	parse_export(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]))
	{
		while (var[i])
		{
			if (var[i] == '=')
				return (0);
			if (ft_isalnum(var[i]) == 0)
				break ;
			i++;
		}
	}
	printf("export: `%s': not a valid identifier\n", var);
	return (1);
}

int	print_export(t_global *glo)
{
	int		i;
	char	*var_name;
	char	*var_content;

	var_name = NULL;
	var_content = NULL;
	i = 0;
	while (glo->env[i])
	{
		if (ft_strncmp(glo->env[i], "_", 1) != 0)
		{
			var_name = ft_var_name(glo->env[i]);
			if (!var_name)
				return (1);
			var_content = ft_getenv(glo->env, var_name);
			if (!var_content)
			{
				free(var_name);
				return (1);
			}
			printf("export %s=\"%s\"\n", var_name, var_content);
			free(var_name);
		}
		i++;
	}
	return (0);
}

int	ft_export(t_global *glo)
{
	int		i;
	char	*var_name;
	int		return_value;
	int		is_line;

	i = 1;
	return_value = 0;
	if (glo->command->args[1] == NULL)
		return (print_export(glo));
	while (glo->command->args[i])
	{
		if (parse_export(glo->command->args[i]) == 0)
		{
			var_name = ft_var_name(glo->command->args[i]);
			if (!var_name)
				return (1);
			is_line = find_var_in_env(glo->env, var_name);
			free(var_name);
			if (is_line == -1 && add_env_var(glo, glo->command->args[i]) == 1)
			{
				printf("export: erreur malloc\n");
				return (1);
			}
			if (is_line != -1 && change_env_var(glo, glo->command->args[i],
					is_line) == 1)
				return (1);
		}
		else
			return_value = 1;
		i++;
	}
	return (return_value);
}
