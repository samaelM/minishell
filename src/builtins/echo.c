/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:19:17 by ahenault          #+#    #+#             */
/*   Updated: 2024/10/15 21:47:56 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_echo(t_command *command)
{
	int	i;
	int	new_line;

	i = 1;
	new_line = 0;
	if (command->args[1] && ft_strncmp(command->args[1], "-n", 3) == 0)
	{
		i++;
		new_line = 1;
	}
	while (command->args[i])
	{
		printf("%s", command->args[i]);
		if (command->args[i + 1])
			printf(" ");
		i++;
	}
	if (new_line == 0)
		printf("\n");
	return (0);
}
