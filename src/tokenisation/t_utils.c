/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_utils.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:21:21 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/05 18:00:57 by maemaldo         ###   ########.fr       */
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
		if (!str[idx])
			return (-1);
		if (str[idx])
			idx++;
	}
	return (idx);
}
// #include <time.h>

int	ft_redir_len(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] && is_in_set(str[idx], "><"))
	{
		while (str[idx] && is_in_set(str[idx], "<>"))
			idx++;
		while (str[idx] && is_in_set(str[idx], " 	"))
			idx++;
		while (str[idx] && !is_in_set(str[idx], " 	"))
		{
			// printf("redir0:%d:%c (%s)\n", idx, str[idx], str+idx);
			idx += ft_skipquotes(str + idx, '"');
			// printf("redir1:%d:%c (%s)\n", idx, str[idx], str+idx);
			idx += ft_skipquotes(str + idx, '\'');
			// printf("redir2:%d:%c (%s)\n", idx, str[idx], str+idx);
			// sleep(1);
			if (!is_in_set(str[idx], " 	'\""))
				idx++;
		}
		while (str[idx] && is_in_set(str[idx], " 	"))
			idx++;
	}
	return (idx);
}
