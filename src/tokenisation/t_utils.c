/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:21:21 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/26 17:34:28 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenisation.h"

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
	while (str[idx] && is_in_set(str[idx], "<>'\""))
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
	// printf("len redir = %d\n", idx);
	return (idx);
}
