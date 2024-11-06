/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:28:47 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/06 17:29:57 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

void	perr(char *str)
{
	write(STDERR_FILENO, str, ft_strlen(str));
}

int	ft_error_token(char *str)
{
	printf("syntax error near unexpected token `%s'\n", str);
	return (-1);
}
