/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:19:17 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/14 21:25:17 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	print_echo(t_command *command, int i, int new_line)
{
	while (command->args[i])
	{
		write(1, command->args[i], ft_strlen(command->args[i]));
		if (command->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (new_line == 1)
		write(1, "\n", 1);
}

int	ft_echo(t_command *command)
{
	int	i;
	int	j;
	int	new_line;

	i = 1;
	new_line = 1;
	while (command->args[i] && command->args[i][0] == '-'
		&& command->args[i][1] == 'n')
	{
		j = 1;
		while (command->args[i][j] == 'n')
			j++;
		if (command->args[i][j] != '\0')
			break ;
		i++;
		new_line = 0;
	}
	print_echo(command, i, new_line);
	return (0);
}
