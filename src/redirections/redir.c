/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/10 14:12:19 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_redir(t_command *cmd, char *line)
{
	int	i;

	if (!cmd)
		return (0);
	i = 0;
	while (line[i])
	{
		if (ft_strncmp(line + i, ">>", 2) == 0)
			i += ft_outfile2(cmd, line + i);
		else if (line[i] == '>')
			i += ft_outfile(cmd, line + i);
		else if (ft_strncmp(line + i, "<<", 2) == 0)
			i += ft_heredoc(cmd, line + i);
		else if (line[i] == '<')
			i += ft_infile(cmd, line + i);
		while (line[i] && !is_in_set(line[i], "><|"))
			i++;
		if (line[i] == '|')
		{
			i++;
			cmd = cmd->next;
		}
	}
	return (1);
}
