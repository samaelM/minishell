/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 19:22:30 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/31 14:42:17 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	nb_args(char **args)
{
	int	i;

	i = 0;
	while (args[i])
		i++;
	return (i);
}

int	is_nb(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] == 32 || cmd[i] == '\0')
	{
		if (cmd[i] == '\0')
			return (1);
		i++;
	}
	if (cmd[i] == '+' || cmd[i] == '-')
		i++;
	while (ft_isdigit(cmd[i]))
		i++;
	while (cmd[i] == 32)
		i++;
	if (cmd[i] != '\0')
		return (1);
	return (0);
}

int	exit_nb(t_global *g, char *cmd)
{
	int	nb;

	nb = ft_atoi(cmd);
	ft_free_glob(g);
	exit(nb % 256);
}

int	ft_exit(t_global *g)
{
	printf("exit\n");
	if (nb_args(g->command->args + 1) == 0)
	{
		ft_free_glob(g);
		exit(g->exit_value);
	}
	if (is_nb(g->command->args[1]) || ft_strlen(g->command->args[1]) > 19
		|| (ft_strlen(g->command->args[1]) == 19
			&& ft_strncmp("9223372036854775807", g->command->args[1], 19) < 0))
	{
		printf("exit: %s: numeric argument required\n", g->command->args[1]);
		ft_free_glob(g);
		exit(2);
	}
	if (is_nb(g->command->args[1]) == 0 && nb_args(g->command->args + 1) == 1)
		exit_nb(g, g->command->args[1]);
	printf("exit: too many arguments\n");
	return (1);
}
