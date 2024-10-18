/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:29:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/16 16:42:01 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// need protection
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
		perror(name);
		free(name);
		return (-1);
	}
	free(name);
	return (len + 1);
}

// need protection
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
	if (name_size==-1)
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
		perror(name);
		free(name);
		return (-1);
	}
	free(name);
	return (len + 2);
}

// need protection
int	ft_infile(t_global *global, char *line)
{
	int			name_size;
	int			len;
	char		*name;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->infile > 1)
		close(cmd->infile);
	if (cmd->is_heredoc)
	{
		unlink("/tmp/heredoc");
		cmd->is_heredoc = 0;
	}
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
		perror(name);
		free(name);
		return (-1);
	}
	free(name);
	return (len + 1);
}

// need protection
int	ft_heredoc(t_global *global, char *line)
{
	int			len;
	int			size;
	char		*lim;
	char		*buff;
	char		*line2;
	t_command	*cmd;

	cmd = global->tmp;
	if (cmd->infile > 1)
		close(cmd->infile);
	if (cmd->is_heredoc)
		unlink(HEREDOC_NAME);
	buff = malloc(700 * sizeof(char));
	if (!buff)
		return (-1);
	len = 0;
	size = ft_size_token(global, line + 2);
	if (size == -1)
		return (-1);
	lim = ft_calloc(size + 1, sizeof(char));
	if (!lim)
		return (perr(ERR_ALLOC), -1);
	ft_get_arg(global, lim, line + 2);
	cmd->infile = open(HEREDOC_NAME, O_CREAT | O_RDWR, 0666);
	while (42)
	{
		line2 = readline(">");
		if (ft_strncmp(lim, line2, ft_strlen(lim)) == 0
			&& ft_strlen(lim) == ft_strlen(line2))
			break ;
		write(cmd->infile, line2, ft_strlen(line2));
		write(cmd->infile, "\n", 1);
	}
	close(cmd->infile);
	cmd->infile = open(HEREDOC_NAME, O_RDONLY);
	printf("fd=%d\n", cmd->infile);
	printf("%zd\n", read(cmd->infile, buff, 700));
	printf(">%s<\n", buff);
	free(buff);
	cmd->is_heredoc = 1;
	return (len + 2);
}
