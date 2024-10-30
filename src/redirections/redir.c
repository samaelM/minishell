/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/30 19:33:45 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

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
			return (0);
		i += tmp;
		while (line[i] && !is_in_set(line[i], "><|"))
		{
			if (!is_in_set(line[i], "'\""))
				i++;
			i += ft_skipquotes(line + i, '"');
			// printf("1:%c\n", line[i]);
			i += ft_skipquotes(line + i, '\'');
			// printf("2:%c\n", line[i]);
			if (line[i] == '|')
			{
				i++;
				global->tmp = global->tmp->next;
			}
		}
	}
	return (1);
}
