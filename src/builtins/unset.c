/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/25 14:46:36 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/04 18:48:00 by ahenault         ###   ########.fr       */
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
	{
		ft_perrorf("pas trouve\n");
		return (1);
	}
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
	while (glob->command->args[i])
	{
		ft_perrorf("unset: %s\n", glob->command->args[i]);
		if (ft_strncmp(glob->command->args[i], "_", 1) == 0)
			change_env_var(glob, "_=_", find_var_in_env(glob->env, "_"));
		else
			unset_this_line(glob->env, find_var_in_env(glob->env,
					glob->command->args[i]));
		i++;
	}
	return (0);
}
