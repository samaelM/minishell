/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:59 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/18 19:28:06 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_env(t_global *glob)
{
	int	i;

	i = 0;
	while (glob->env[i])
	{
		printf("%s\n", glob->env[i]);
		i++;
	}
	return (0);
}

char	*coller_deux_strings(char *s1, char *s2)
{
	char	*string;
	int		size_s1;
	int		size_s2;

	size_s1 = ft_strlen(s1);
	size_s2 = ft_strlen(s2);
	string = malloc(sizeof(char) * (size_s1 + size_s2));
	if (!string)
	{
		printf("erreur malloc\n");
		return (NULL);
	}
	ft_strlcpy(string, s1, size_s1 + 1);
	ft_strlcat(string, s2, size_s1 + size_s2 + 1);
	printf("string %s\n", string);
	return (string);
}

char	**create_env_i(void)
{
	char	**env_tab;

	env_tab = malloc(sizeof(char *) * 4);
	if (!env_tab)
	{
		printf("erreur malloc\n");
		return (NULL);
	}
	env_tab[0] = ft_strdup(coller_deux_strings("PWD=", ft_getcwd()));
	env_tab[1] = ft_strdup(coller_deux_strings("SHLVL=", "1"));
	env_tab[2] = ft_strdup(coller_deux_strings("_=", "/minishell"));
	if (!env_tab[0] || !env_tab[1] || !env_tab[2])
	{
		free_tab(env_tab);
		exit(1);
	}
	env_tab[3] = NULL;
	return (env_tab);
}

char	*change_shlvl(char *var)
{
	char	*content;
	int		i;

	// printf("content %s\n", var);
	content = ft_var_content(var);
	// printf("content %s\n", content);
	i = ft_atoi(content) + 1;
	// printf("i %i\n", i);
	var = coller_deux_strings("SHLVL=", ft_itoa(i));
	return (var);
}

char	**create_our_env(char **envp)
{
	int		i;
	char	**env_tab;

	if (envp[0] == NULL)
	{
		printf("error no envp\n");
		return (create_env_i());
	}
	i = 0;
	while (envp[i])
		i++;
	env_tab = malloc(sizeof(char *) * (i + 1));
	if (!env_tab)
	{
		printf("erreur malloc\n");
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "SHLVL=", 6) == 0)
			env_tab[i] = change_shlvl(envp[i]);
		else
		{
			env_tab[i] = ft_strdup(envp[i]);
			if (!env_tab[i])
			{
				printf("erreur strdup\n");
				free_tab(env_tab);
				return (NULL);
			}
		}
		i++;
	}
	env_tab[i] = NULL;
	return (env_tab);
}
