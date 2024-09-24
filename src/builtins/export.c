/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 12:48:08 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/04 20:28:57 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// add
// modify
// delete

// pas de _


// int change_env_var(t_list *env_list, char *var)
// {
// 	char *buf = NULL;

// 	printf("%s\n", (char *)env_list->content);
// 	ft_bzero(env_list->content, ft_strlen(env_list->content));
// 	ft_strlcat(env_list->content, var, ft_strlen(var) + 1);
// 	if (ft_strncmp(var, "PWD=", 4) == 0)
// 		ft_strlcat(env_list->content, getcwd(buf, PATH_MAX), PATH_MAX + 1);
// 	// else
// 	// 	ft_strlcat(env_list->content, getcwd(buf, PATH_MAX), PATH_MAX + 1);
// 	printf("%s\n", (char *)env_list->content);
// 	return (0);
// }

// int add_env_var(t_list *env_list, char *var)
// {
// //	printf("%s\n", (char *)env_list->content);
// 	ft_lstadd_back(&env_list, ft_lstnew(var));
// 	//printf("%s\n", (char *)env_list->content);
// 	return (0);
// }

// si tu touves avec strcmp, tu change
// int ft_export(t_command *command, t_list *env_list)
// {
// 	int i = 1;
	
// 	// if(command->args[1] == NULL)
// 	//	print export + var dans l'ordre ascii
// 	while(command->args[i])
// 	{
// 		t_list *tmp = find_var_in_env(env_list, command->args[i]);
// 		if(tmp != NULL)
// 			change_env_var(tmp, command->args[i]);
// 		else
// 		{
// 			printf("pas trouve la variable il faudra add\n");
// 			// sinon tu add nvlle var
// 			//add_env_var(tmp, command->args[i]);
// 		}
// 		i++;
// 	}
// //	printf("c ici %i\n", find_env(command, env_list, "PWD="));
// 	return (0);
// }

// int ft_export(t_command *command)
// {
// 	int i = 1;
	
// 	// if(command->args[1] == NULL)
// 	//	print export + var dans l'ordre ascii
// 	while(command->args[i])
// 	{
// 		// t_list *tmp = find_var_in_env(env_list, command->args[i]);
// 		// if(tmp != NULL)
// 		// 	change_env_var(tmp, command->args[i]);
// 		// else
// 		// {
// 		// 	printf("pas trouve la variable il faudra add\n");
// 		// 	// sinon tu add nvlle var
// 		// 	//add_env_var(tmp, command->args[i]);
// 		// }
// 		i++;
// 	}
// //	printf("c ici %i\n", find_env(command, env_list, "PWD="));
// 	return (0);
// }


// int change_env_var(t_list *env_list, char *var)
// {
// 	char *buf = NULL;

// 	printf("%s\n", (char *)env_list->content);
// 	ft_bzero(env_list->content, ft_strlen(env_list->content));
// 	ft_strlcat(env_list->content, var, ft_strlen(var) + 1);
// 	if (ft_strncmp(var, "PWD=", 4) == 0)
// 		ft_strlcat(env_list->content, getcwd(buf, PATH_MAX), PATH_MAX + 1);
// 	// else
// 	// 	ft_strlcat(env_list->content, getcwd(buf, PATH_MAX), PATH_MAX + 1);
// 	printf("%s\n", (char *)env_list->content);
// 	return (0);
// }

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
			i++;
	}
	tab[i] = ft_strdup(var);
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

// int add_export_tab(t_global *glo, char *var)
// {
// 	// cree un tab export, ajouter export a chaque fois
// 	// si aucun arg print export + var dans l'ordre ascii
// }

// cd home unset
// _last cmd


int ft_export(t_global *glo)
{
	int i = 1;
	char *var_name;
	// if(command->args[1] == NULL)
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
		//add_export_tab();
		i++;
	}
	return (0);
}

