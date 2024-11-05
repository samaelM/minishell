/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:29:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/05 13:36:17 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_outfile(t_global *global, char *line)
{
	int			name_size;
	int			len;
	char		*name;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->outfile > 1)
		close(cmd->outfile);
	len = 0;
	name_size = ft_size_token(global, line + 1);
	if (name_size == -1)
		return (-1);
	name = ft_calloc(name_size + 1, sizeof(char));
	if (!name)
		return (perr(ERR_ALLOC), -1);
	len = ft_get_arg(global, name, line + 1);
	if (len == -1)
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
	return (len + 1);
}

int	ft_outfile2(t_global *global, char *line)
{
	int			name_size;
	int			len;
	char		*name;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->outfile > 1)
		close(cmd->outfile);
	len = 0;
	name_size = ft_size_token(global, line + 2);
	if (name_size == -1)
		return (-1);
	name = ft_calloc(name_size + 1, sizeof(char));
	if (!name)
		return (perr(ERR_ALLOC), -1);
	len = ft_get_arg(global, name, line + 2);
	if (len == -1)
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
	return (len + 2);
}

int	ft_infile(t_global *global, char *line)
{
	int			name_size;
	int			len;
	char		*name;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->infile > 1)
		close(cmd->infile);
	len = 0;
	name_size = ft_size_token(global, line + 1);
	if (name_size == -1)
		return (-1);
	name = ft_calloc(name_size + 1, sizeof(char));
	if (!name)
		return (perr(ERR_ALLOC), -1);
	len = ft_get_arg(global, name, line + 1);
	cmd->infile = open(name, O_RDONLY);
	if (cmd->infile == -1)
	{
		cmd->infile = -2;
		global->exit_value = 1;
		perror(name);
		free(name);
		return (-1);
	}
	free(name);
	return (len + 1);
}
