/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:48:08 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/11 20:36:58 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int add_env_var(t_global *glo, char *var)
{
	char **tab;
	int i;

	i = 0;
	while(glo->env[i])
	 	i++;
	tab = malloc(sizeof(char *) * (i + 2));
	if(!tab)
		return (1);
	i = 0;
	while(glo->env[i])
	{
		tab[i] = ft_strdup(glo->env[i]);
		free(glo->env[i]);
		if(!tab[i])
			return (1);
		i++;
	}
	tab[i] = ft_strdup(var);
	if(!tab[i])
		return (1);
	tab[i + 1] = NULL;
	free(glo->env);
	glo->env = tab;
	return (0);
}

int change_env_var(t_global *glo, char *var, int line)
{
	free(glo->env[line]);
	glo->env[line] = ft_strdup(var);
	if(!glo->env[line])
		return (1); 
	return (0);
}

int parse_export(char *var)
{
	int i = 0;
	if((var[i] >= 'a' && var[i] <= 'z') || (var[i] >= 'A' && var[i] <= 'Z'))
		i++;
	while (i != 0 && var[i])
	{
		if(var[i] == '=')
			return (0);
		i++;
	}
	printf("export: `%s': not a valid identifier\n", var);
	return (1);
}

void print_export(t_global *glo)
{
	int i;
	
	i = 0;
	while(glo->env[i])
	{
		printf("export %s\n", glo->env[i]);
		i++;
	}
}

int ft_export(t_global *glo)
{
	int i = 1;
	char *var_name;
	int return_value = 0;
	
	if(glo->command->args[1] == NULL)
	{
		print_export(glo);
		return (0);
	}
	while(glo->command->args[i])
	{
		if(parse_export(glo->command->args[i]) == 0)
		{
			var_name = ft_var_name(glo->command->args[i]);
			int is_line = find_var_in_env(glo->env, var_name);
			free(var_name);
			if(is_line == -1 && add_env_var(glo, glo->command->args[i]) == 1)
				return(1);
			if(is_line != -1 && change_env_var(glo, glo->command->args[i], is_line) == 1)
				return(1);
		}
		else
			return_value = 1;
		i++;
	}
	return (return_value);
}

