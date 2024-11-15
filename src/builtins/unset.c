/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:46:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 14:52:35 by ahenault         ###   ########.fr       */
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

int	ft_unset(t_global *glob)
{
	int	i;

	i = 1;
	while (glob->tmp->args[i])
	{
		if (ft_strncmp(glob->tmp->args[i], "_", 1) == 0)
			change_env_var(glob, "_=_", find_var_in_env(glob->env, "_"));
		else
			unset_this_line(glob->env, find_var_in_env(glob->env,
					glob->tmp->args[i]));
		i++;
	}
	return (0);
}
