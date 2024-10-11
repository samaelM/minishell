/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_arg.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 16:19:14 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/10 16:26:40 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_tokencpy(char *dest, char *src, int *pos)
{
	int	idx;

	idx = 0;
	if (src[idx] == '$')
	{
		ft_sstrlcpy(dest + (*pos), ft_env_var(src + idx + 1), ft_env_len_bis(src
				+ idx + 1) + 1);
		(*pos) += ft_env_len_bis(src + idx + 1);
		idx += ft_envname_len(src + idx + 1);
	}
	else
		dest[(*pos)++] = src[idx];
	idx++;
	return (idx);
}

int	ft_get_arg(char *dest, char *str)
{
	int	idx;
	int	pos;

	pos = 0;
	idx = 0;
	while (str[idx] && is_in_set(str[idx], " 	"))
		idx++;
	while (str[idx] && !is_in_set(str[idx], " 	|"))
	{
		if (str[idx] && str[idx] == '"')
		{
			idx++;
			while (str[idx] && str[idx] != '"')
				idx += ft_tokencpy(dest, str + idx, &pos);
			idx++;
		}
		if (str[idx] && str[idx] == '\'')
		{
			idx++;
			while (str[idx] && str[idx] != '\'')
				dest[pos++] = str[idx++];
			idx++;
		}
		while (str[idx] && !is_in_set(str[idx], "\"' 	|<>"))
			idx += ft_tokencpy(dest, str + idx, &pos);
		while (str[idx] && is_in_set(str[idx], "<>"))
			idx += ft_redir_len(str + idx);
	}
	dest[pos] = 0;
	return (idx);
}
