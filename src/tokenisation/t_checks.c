/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_checks.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:43:39 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 15:30:31 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenisation.h"

static int	ft_check_pipes(char *str)
{
	int	idx;

	if (*str != '|')
		return (0);
	idx = 1;
	while (is_in_set(str[idx], " 	"))
		idx++;
	if (!str[idx] || str[idx] == '|')
		return (ft_error_token("|"));
	idx++;
	return (1);
}

static char	*ft_get_token(char *str)
{
	if (ft_strncmp(str, ">>", 2) == 0)
		return ((">>"));
	if (*str == '>')
		return ((">"));
	if (ft_strncmp(str, "<<", 2) == 0)
		return (("<<"));
	if (*str == '<')
		return (("<"));
	return (("|"));
}

static int	ft_check_redir(char *str)
{
	int	idx;

	if (!*str || !is_in_set(*str, "><"))
		return (0);
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
	return (idx);
}

static int	ft_checks(char *str)
{
	int	idx;
	int	tmp;

	tmp = 0;
	idx = 0;
	while (str[idx] && !is_in_set(str[idx], "><|\"'"))
		idx++;
	tmp = ft_skipquotes(str + idx, '"');
	if (tmp == -1)
		return (perr("quote `\"` not closed\n"), 0);
	idx += tmp;
	tmp = ft_skipquotes(str + idx, '\'');
	if (tmp == -1)
		return (perr("quote `'` not closed\n"), 0);
	idx += tmp;
	tmp = ft_check_pipes(str + idx);
	if (tmp == -1)
		return (0);
	idx += tmp;
	tmp = ft_check_redir(str + idx);
	if (tmp == -1)
		return (0);
	idx += tmp;
	return (idx);
}

int	ft_check_line(t_global *global)
{
	int	idx;
	int	tmp;

	idx = 0;
	if (g_sig == SIGINT)
		global->exit_value = 130;
	if (global->line == NULL)
		signal_ctrd(global);
	if (*global->line)
		add_history(global->line);
	while (global->line[idx] && is_in_set(global->line[idx], " 	"))
		idx++;
	if (global->line[idx] == '|')
		return (ft_error_token("|"), 0);
	while (global->line[idx])
	{
		tmp = ft_checks(global->line + idx);
		if (tmp <= 0)
			return (tmp);
		idx += tmp;
	}
	return (1);
}
