/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:46:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 15:28:12 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	unset_this_line(char **env, int l)
{
	int		i;
	int		j;
	char	*tmp;

	i = l;
	j = l + 1;
	if (l == -1)
		return (1);
	tmp = env[l];
	while (env[i])
	{
		env[i] = env[j];
		i++;
		j++;
	}
	free(tmp);
	return (0);
}

int	ft_unset(t_global *g)
{
	int	i;

	i = 1;
	while (g->tmp->args[i])
	{
		if (ft_strncmp(g->tmp->args[i], "_", 1) == 0)
			change_env_var(g, "_=_", find_var_in_env(g->env, "_"));
		else
			unset_this_line(g->env, find_var_in_env(g->env, g->tmp->args[i]));
		i++;
	}
	return (0);
}
