/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/01 18:49:21 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	skip_cmd(char *line)
{
	int	i;

	i = 0;
	while (line[i] && line[i] != '|')
		i++;
	return (i);
}

int	ft_redir(t_global *global, char *line)
{
	int	i;
	int	tmp;

	if (!global->command)
		return (0);
	global->tmp = global->command;
	i = 0;
	tmp = 0;
	while (line[i])
	{
		if (ft_strncmp(line + i, ">>", 2) == 0)
			tmp = ft_outfile2(global, line + i);
		else if (line[i] == '>')
			tmp = ft_outfile(global, line + i);
		else if (ft_strncmp(line + i, "<<", 2) == 0)
			tmp = ft_heredoc(global, line + i);
		else if (line[i] == '<')
			tmp = ft_infile(global, line + i);
		if (tmp < 0)
			i += skip_cmd(line);
		i += tmp;
		while (line[i] && !is_in_set(line[i], "><|"))
		{
			if (!is_in_set(line[i], "'\""))
				i++;
			i += ft_skipquotes(line + i, '"');
			i += ft_skipquotes(line + i, '\'');
			if (line[i] == '|')
			{
				i++;
				global->tmp = global->tmp->next;
			}
		}
	}
	return (1);
}
