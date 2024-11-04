/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:42:07 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/04 13:25:35 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	ft_hd_return(int fd[2], char *line, t_global *global)
{
	close(fd[0]);
	close(fd[1]);
	free(line);
	global->tmp->infile = -2;
	return (-1);
}

static ssize_t	write_all(int fd, const void *buffer, size_t count)
{
	const char	*buf;
	size_t		total_written;
	ssize_t		bytes_written;

	buf = buffer;
	total_written = 0;
	while (total_written < count)
	{
		bytes_written = write(fd, buf + total_written, count - total_written);
		if (bytes_written > 0)
			total_written += bytes_written;
		else if (bytes_written == -1)
		{
			if (errno == EAGAIN || errno == EWOULDBLOCK)
				continue ;
			else
				return (-1);
		}
	}
	write(fd, "\n", 1);
	return (total_written);
}

// malloc sensitive
static int	ft_hd_nquote(t_global *global, int fd[2], char *lim)
{
	char	*here_line;
	char	*new_line;

	while (42)
	{
		here_line = readline("heredoc (parsed)> ");
		if (!here_line)
		{
			perr(ERR_HD_EOF);
			break ;
		}
		if (ft_strncmp(here_line, lim, ft_strlen(lim)) == 0
			&& here_line[ft_strlen(lim)] == 0)
			break ;
		new_line = ft_hd_parse(global, here_line);
		if (!new_line)
			return (ft_hd_return(fd, here_line, global));
		write_all(fd[1], new_line, ft_strlen(new_line));
		(free(here_line), free(new_line));
	}
	free(lim);
	free(here_line);
	close(fd[1]);
	global->command->infile = fd[0];
	return (2);
}

static int	ft_hd_quote(t_global *global, int fd[2], char *lim)
{
	char	*here_line;

	while (42)
	{
		here_line = readline("heredoc (not parsed)> ");
		if (!here_line)
		{
			perr(ERR_HD_EOF);
			break ;
		}
		if (ft_strncmp(here_line, lim, ft_strlen(lim)) == 0
			&& here_line[ft_strlen(lim)] == 0)
			break ;
		write_all(fd[1], here_line, ft_strlen(here_line));
		free(here_line);
	}
	free(lim);
	free(here_line);
	close(fd[1]);
	global->command->infile = fd[0];
	return (2);
}

// malloc sensitive
int	ft_heredoc(t_global *global, char *line)
{
	char	*lim;
	int		fd[2];
	int		in_quote;

	in_quote = 0;
	lim = ft_getlim(global, line, &in_quote);
	if (!lim)
		return (perr("pas de lim\n"), -1);
	if (pipe(fd) == -1)
		return (free(lim), -1);
	if (in_quote)
		return (ft_hd_quote(global, fd, lim));
	return (ft_hd_nquote(global, fd, lim));
}
