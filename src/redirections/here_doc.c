/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/01 16:42:07 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/01 18:53:17 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

ssize_t	write_all(int fd, const void *buffer, size_t count)
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
	return (total_written);
}

//malloc sensitive
int	ft_hd_nquote(t_global *global, int fd[2], char *lim)
{
	char	*here_line;
	char	*new_line;

	if (pipe(fd) == -1)
		return (free(lim), -1);
	while (1)
	{
		here_line = readline("heredoc (parsed)> ");
		if (!here_line)// ctrld
			break ;
		if (ft_strncmp(here_line, lim, ft_strlen(lim)) == 0
			&& here_line[ft_strlen(lim)] == 0)
			break ;
		new_line = ft_hd_parse(global, here_line);
		if (!new_line)//close pipe et set infile to -2
			return (-1);
		write_all(fd[1], new_line, ft_strlen(new_line));
		write(fd[1], "\n", 1);
		free(here_line);
		free(new_line);
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

	if (pipe(fd) == -1)
		return (free(lim),perr("error pipe\n"), 1);
	while (1)
	{
		here_line = readline("heredoc (not parsed)> ");
		if (!here_line)//ctrld
			break ;
		if (ft_strncmp(here_line, lim, ft_strlen(lim)) == 0
			&& here_line[ft_strlen(lim)] == 0)
			break ;
		write_all(fd[1], here_line, ft_strlen(here_line));
		write(fd[1], "\n", 1);
		free(here_line);
	}
	free(lim);
	free(here_line);
	close(fd[1]);
	global->command->infile = fd[0];
	return (2);
}

//malloc sensitive
int	ft_heredoc(t_global *global, char *line)
{
	char	*lim;
	int		fd[2];
	int		in_quote;

	in_quote = 0;
	lim = ft_getlim(global, line, &in_quote);
	if (!lim)
		return (perr("pas de lim\n"),-1);
	if (in_quote)
		return (ft_hd_quote(global, fd, lim));
	return (ft_hd_nquote(global, fd, lim));
}
