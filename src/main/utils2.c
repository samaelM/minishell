/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 17:28:47 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/21 13:06:23 by maemaldo         ###   ########.fr       */
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
	ft_perrorf("mini: syntax error near unexpected token `%s'\n", str);
	return (-1);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (ft_strlen(s1) != ft_strlen(s2))
		return (1);
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
		i++;
	}
	return (0);
}

void	error_dup(t_global *g)
{
	close(g->tmp->pipe[1]);
	close_all_fd_child(g);
	ft_free_glob(g);
	ft_perrorf("exec: error with dup\n");
	exit(1);
}
