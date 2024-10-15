/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_checks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:43:39 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/14 17:30:23 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_error_token(char *str)
{
	printf("syntax error near unexpected token `%s'\n", str);
	return (-1);
}

static int	ft_check_pipes(char *str)
{
	int	idx;

	idx = 1;
	while (is_in_set(str[idx], " 	"))
		idx++;
	if (!str[idx] || str[idx] == '|')
		return (ft_error_token("|"));
	idx++;
	return (idx);
}

static char	*ft_get_token(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return (ft_strdup(">>"));
	if (*str == '>')
		return (ft_strdup(">"));
	if (ft_strncmp(str, "<<", 2) == 0)
		return (ft_strdup("<<"));
	if (*str == '<')
		return (ft_strdup("<"));
	return (ft_strdup("|"));
}

static int	ft_check_redir(char *str)
{
	int	idx;

	idx = 0;
	if (ft_strncmp(str + idx, ">>", 2) == 0)
		idx += 2;
	else if (str[idx] == '>')
		idx++;
	else if (ft_strncmp(str + idx, "<<", 2) == 0)
		idx += 2;
	else if (str[idx] == '<')
		idx++;
	while (str[idx] && is_in_set(str[idx], " 	"))
		idx++;
	if (!str[idx])
		return (ft_error_token("newline"));
	if (is_in_set(str[idx], "><|"))
		return (ft_error_token(ft_get_token(str + idx)));
	idx++;
	return (idx);
}

// need protection
int	ft_check_line(char *str)
{
	int	idx;
	int	pos;

	idx = 0;
	while (str[idx] && is_in_set(str[idx], " 	"))
		idx++;
	if (str[idx] == '|')
		return (ft_error_token("|"), 0);
	while (str[idx])
	{
		pos = 0;
		while (str[idx] && is_in_set(str[idx], " 	"))
			idx++;
		if (str[idx] == '"')
			while (str[idx] && str[idx] != '"')
				idx++;
		if (str[idx] == '|')
			pos = ft_check_pipes(str + idx);
		if (pos == -1)
			return (0);
		idx += pos;
		pos = 0;
		if (is_in_set(str[idx], "><"))
			pos = ft_check_redir(str + idx);
		if (pos == -1)
			return (0);
		idx += pos;
		if (str[idx])
			idx++;
	}
	return (1);
}