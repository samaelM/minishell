/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:59 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 14:12:53 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*concat_strings(char *s1, char *s2)
{
	char	*string;
	int		size_s1;
	int		size_s2;

	if (!s1 || !s2)
		return (NULL);
	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	string = malloc(sizeof(char) * (size_s1 + size_s2) + 1);
	if (!string)
	{
		ft_perrorf("environment creation: error with malloc\n");
		return (NULL);
	}
	ft_strlcpy(string, s1, size_s1 + 1);
	ft_strlcat(string, s2, size_s1 + size_s2 + 1);
	return (string);
}

char	**create_new_env(void)
{
	char	**env_tab;

	env_tab = ft_calloc(4, sizeof(char *));
	if (!env_tab)
	{
		ft_perrorf("environment creation: error with malloc\n");
		exit(1);
	}
	env_tab[0] = concat_strings("PWD=", ft_getcwd());
	if (env_tab[0])
		env_tab[1] = concat_strings("SHLVL=", "1");
	if (env_tab[1])
		env_tab[2] = concat_strings("_=", "/minishell");
	if (!env_tab[2])
	{
		free_tab(env_tab);
		exit(1);
	}
	return (env_tab);
}

char	*change_shlvl(char **env, char *var) // check
{
	char *content;
	int i;
	char *var_name;

	var_name = ft_var_name(var);
	if (!var_name)
		return (NULL);
	content = ft_getenv(env, var_name);
	free(var_name);
	if (!content)
		return (NULL);
	i = ft_atoi(content) + 1;
	content = ft_itoa(i);
	var = concat_strings("SHLVL=", content);
	free(content);
	return (var);
}

char	**copy_env(char **env_tab, char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
		{
			env_tab[i] = change_shlvl(envp, envp[i]);
			if (!env_tab[i])
				return (NULL);
		}
		else
		{
			env_tab[i] = ft_strdup(envp[i]);
			if (!env_tab[i])
				return (NULL);
		}
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}

char	**create_env(char **envp)
{
	int		i;
	char	**env_tab;

	if (envp[0] == NULL)
		return (create_new_env());
	i = 0;
	while (envp[i])
		i++;
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
	{
		ft_perrorf("environment creation: error with malloc\n");
		exit(1);
	}
	env_tab = copy_env(env_tab, envp); // check leaks
	if (!env_tab)
	{
		free_tab(env_tab);
		ft_perrorf("environment creation: error with malloc\n");
		exit(1);
	}
	return (env_tab);
}
