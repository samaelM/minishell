/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:48:08 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/08 17:57:51 by ahenault         ###   ########.fr       */
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
		tab[i] = ft_strdup(glo->env[i]); // a proteger
			i++;
	}
	tab[i] = ft_strdup(var); // a proteger
	tab[i + 1] = NULL;
	glo->env = tab;
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
			return (1);
		i++;
	}
	printf("export: `%s': not a valid identifier\n", var);
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

char *ft_var_name(char *var)
{
	int i = 0;
	while(var[i] && var[i] != '=')
		i++;
	char *new_line = malloc(sizeof(char) * i + 1);
	if(!new_line)
		return NULL;
	i = 0;
	while(var[i] && var[i] != '=')
	{
		new_line[i] = var[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

int print_export(t_global *glo)
{
	int i;
	int size;
	int j;
	char *line;
	
	j = 0;
	size = 0;
	line= glo->env[0];
	while(glo->env[size])
		size++;
	//while(j < size)
	{
		i = 0;
		while(glo->env[i])
		{
			// if (ft_strncmp(line, glo->env[i], 500) > 0)
			 	line = glo->env[i];
			printf("export %s\n", line);
			i++;
		}
		// printf("export %s\n", line);
		j++;
	}
	return (0);
}

int ft_export(t_global *glo)
{
	int i = 1;
	char *var_name;
	
	if(glo->command->args[1] == NULL)
	{
		print_export(glo);
		return (0);
	}
	while(glo->command->args[i])
	{
		if(parse_export(glo->command->args[i]) == 1)
		{
			var_name = ft_var_name(glo->command->args[i]);
			int is_line = find_var_in_env(glo->env, var_name);
			free(var_name);
			if(is_line == -1)
				add_env_var(glo, glo->command->args[i]);
			else
				change_env_var(glo, glo->command->args[i], is_line);
		}
		i++;
	}
	return (0);
}

