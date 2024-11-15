/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:42:07 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 15:09:08 by maemaldo         ###   ########.fr       */
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
int	ft_hd_nquote(t_global *global, int fd[2], char *lim)
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

int	ft_hd_quote(t_global *global, int fd[2], char *lim)
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
char	*ft_hd_parse(t_global *global, char *line)
{
	char	*new_line;

	new_line = ft_init_hd_tk(global, line);
	if (!new_line)
		return (perr(ERR_ALLOC), NULL);
	new_line = ft_fill_hd_tk(global, line, new_line);
	if (!new_line)
		return (NULL);
	return (new_line);
}
