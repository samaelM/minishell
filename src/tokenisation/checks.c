/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:43:39 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/02 16:14:51 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_check_pipes(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (is_in_set(str[i], " 	"))
		i++;
	if (str[i] == '|')
		return (i);
	while (str[i])
	{
		if (str[i] == '|')
		{
			j = i;
			i++;
			while (is_in_set(str[i], " 	"))
				i++;
			if (!str[i] || str[i] == '|')
				return (j);
		}
		i++;
	}
	return (-1);
}

int	ft_check_redir(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && is_in_set(str[i], "><"))
		{
			j = i;
			if (ft_strncmp(str + i, ">>", 2) == 0)
				i += 2;
			else if (str[i] == '>')
				i++;
			else if (ft_strncmp(str + i, "<<", 2) == 0)
				i += 2;
			else if (str[i] == '<')
				i++;
			while (str[i] && is_in_set(str[i], " 	"))
				i++;
			if (!str[i] || is_in_set(str[i], "><|"))
				return (i);
		}
		i++;
	}
	return (-1);
}

int	ft_check_line(char *str)
{
	int	i;

	i = 0;
	if (ft_check_pipes(str) > -1)
	{
		printf("syntax error near unexpected token `%c'\n",
			str[ft_check_pipes(str)]);
		return (0);
	}
	i = ft_check_redir(str);
	if (i > -1)
	{
		if (!str[i])
			printf("syntax error near unexpected token `newline'\n");
		else
			printf("syntax error near unexpected token `%c'(%d)\n", str[i], i);
		return (0);
	}
	return (1);
}
int	ft_check_pipes_bis(char *str)
{
	int	i;

	i = 1;
	while (is_in_set(str[i], " 	"))
		i++;
	if (!str[i] || str[i] == '|')
		return (ft_error_token(ft_strdup("|")));
	i++;
	return (i);
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

int	ft_check_redir_bis(char *str)
{
	int	i;
	int	j;

	i = 0;
	// while (str[i] && is_in_set(str[i], "><"))
	// {
	j = i;
	if (ft_strncmp(str + i, ">>", 2) == 0)
		i += 2;
	else if (str[i] == '>')
		i++;
	else if (ft_strncmp(str + i, "<<", 2) == 0)
		i += 2;
	else if (str[i] == '<')
		i++;
	while (str[i] && is_in_set(str[i], " 	"))
		i++;
	if (!str[i])
		return (ft_error_token(ft_strdup("newline")));
	if (is_in_set(str[i], "><|"))
		return (ft_error_token(ft_get_token(str + i)));
	// }
	i++;
	return (i);
}
int	ft_check_line_bis(char *str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && is_in_set(str[i], " 	"))
		i++;
	if (str[i] == '|')
		return (ft_error_token(ft_strdup("|")), 0); // error
	while (str[i])
	{
		j = 0;
		while (str[i] && is_in_set(str[i], " 	"))
			i++;
		if (str[i] == '"')
			while (str[i] && str[i] != '"')
				i++;
		if (str[i] == '|')
			j = ft_check_pipes_bis(str + i);
		if (j == -1)
			return (0);
		i += j;
		j = 0;
		if (is_in_set(str[i], "><"))
			j = ft_check_redir_bis(str + i);
		if (j == -1)
			return (0);
		i += j;
		i++;
	}
	return (1);
}
