/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/11 18:35:07 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_redir(t_global *global, char *line)
{
	int	i;

	if (!global->command)
		return (0);
	i = 0;
	while (line[i])
	{
		if (ft_strncmp(line + i, ">>", 2) == 0)
			i += ft_outfile2(global, line + i);
		else if (line[i] == '>')
			i += ft_outfile(global, line + i);
		else if (ft_strncmp(line + i, "<<", 2) == 0)
			i += ft_heredoc(global, line + i);
		else if (line[i] == '<')
			i += ft_infile(global, line + i);
		while (line[i] && !is_in_set(line[i], "><|"))
			i++;
		if (line[i] == '|')
		{
			i++;
			global->command = global->command->next;
		}
	}
	return (1);
}
