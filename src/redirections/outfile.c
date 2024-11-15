/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   outfile.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:01:36 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 15:08:50 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_outfile(t_global *global, char *line)
{
	char		*name;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->outfile > 1)
		close(cmd->outfile);
	name = ft_get_file_name(global, line);
	if (!name)
		return (-1);
	cmd->outfile = open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		global->exit_value = 1;
		perror(name);
		free(name);
		return (-1);
	}
	free(name);
	return (1);
}

int	ft_outfile2(t_global *global, char *line)
{
	char		*name;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->outfile > 1)
		close(cmd->outfile);
	name = ft_get_file_name(global, line + 1);
	if (!name)
		return (-1);
	cmd->outfile = open(name, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->outfile == -1)
	{
		cmd->outfile = -2;
		global->exit_value = 1;
		perror(name);
		free(name);
		return (-1);
	}
	free(name);
	return (2);
}
