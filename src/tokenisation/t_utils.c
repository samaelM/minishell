/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:21:21 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/15 20:21:31 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_skipquotes(char *str, char quote)
{
	int	idx;

	idx = 0;
	if (str[idx] && str[idx] == quote)
	{
		idx++;
		while (str[idx] && str[idx] != quote)
			idx++;
		if (str[idx])
			idx++;
	}
	return (idx);
}

int	ft_redir_len(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] && is_in_set(str[idx], "<>"))
	{
		while (str[idx] && is_in_set(str[idx], "<>"))
			idx++;
		while (str[idx] && is_in_set(str[idx], " 	"))
			idx++;
		idx += ft_skipquotes(str + idx, '"');
		idx += ft_skipquotes(str + idx, '\'');
		while (str[idx] && !is_in_set(str[idx], " 	|<>\"'"))
			idx++;
		while (str[idx] && is_in_set(str[idx], " 	"))
			idx++;
	}
	return (idx);
}
