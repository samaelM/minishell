/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:29:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/28 18:52:11 by maemaldo         ###   ########.fr       */
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
// int	ft_heredoc(t_global *global, char *line)
// {
// 	int			len;
// 	int			size;
// 	char		*lim;
// 	char		*buff;
// 	char		*line2;
// 	t_command	*cmd;

// 	cmd = global->tmp;
// 	if (cmd->infile > 1)
// 		close(cmd->infile);
// 	if (cmd->is_heredoc)
// 		unlink(HEREDOC_NAME);
// 	buff = malloc(700 * sizeof(char));
// 	if (!buff)
// 		return (-1);
// 	len = 0;
// 	size = ft_size_token(global, line + 2);
// 	if (size == -1)
// 		return (-1);
// 	lim = ft_calloc(size + 1, sizeof(char));
// 	if (!lim)
// 		return (perr(ERR_ALLOC), -1);
// 	ft_get_arg(global, lim, line + 2);
// 	cmd->infile = open(HEREDOC_NAME, O_CREAT | O_RDWR, 0666);
// 	while (42)
// 	{
// 		line2 = readline(">");
// 		if (ft_strncmp(lim, line2, ft_strlen(lim)) == 0
// 			&& ft_strlen(lim) == ft_strlen(line2))
// 			break ;
// 		write(cmd->infile, line2, ft_strlen(line2));
// 		write(cmd->infile, "\n", 1);
// 	}
// 	close(cmd->infile);
// 	cmd->infile = open(HEREDOC_NAME, O_RDONLY);
// 	printf("fd=%d\n", cmd->infile);
// 	printf("%zd\n", read(cmd->infile, buff, 700));
// 	printf(">%s<\n", buff);
// 	free(buff);
// 	cmd->is_heredoc = 1;
// 	return (len + 2);
// }

char	*ft_get_lim(t_global *global, char *line)
{
	char	*lim;
	int		size;

	size = ft_size_token(global, line + 2);
	if (size == -1)
		return (NULL);
	lim = ft_calloc(size + 1, sizeof(char));
	if (!lim)
		return (perr(ERR_ALLOC), NULL);
	ft_get_arg(global, lim, line + 2);
	return (lim);
}

size_t	ft_getsizelim(char *line)
{
	size_t	idx;
	size_t	len;

	len = 0;
	idx = 0;
	while (is_in_set(line[idx], " 	"))
		idx++;
	while (line[idx] && !is_in_set(line[idx], " 	"))
	{
		if (!is_in_set(line[idx], "'\""))
			len++;
		idx++;
	}
	return (len);
}

char	*ft_getlim(t_global *global, char *line, int *in_quote)
{
	char	*result;
	char	*tmp;

	(void)global;
	line = line + 2;
	result = ft_calloc(ft_getsizelim(line) + 1, sizeof(char));
	tmp = result;
	while (is_in_set(*line, " 	"))
		line++;
	while (*line && !is_in_set(*line, " 	"))
	{
		if (is_in_set(*line, "'\""))
			*in_quote = 1;
		else
			*(tmp++) = *line;
		line++;
	}
	*tmp = 0;
	return (result);
}

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

char	*ft_hd_parse(t_global *global, char *line)
{
	int		idx;
	int		size;
	char	*new_line;
	char	*env_var;

	idx = 0;
	size = 0;
	while (line[idx])
	{
		if (line[idx] == '$')
		{
			size += ft_env_len_bis(global, line + idx + 1);
			if (size == -1)
				return (NULL);
			idx += ft_envname_len(line + idx + 1);
		}
		else
		{
			size++;
			idx++;
		}
	}
	new_line = ft_calloc(size + 1, sizeof(char));
	printf("size = %d\n", size);
	idx = 0;
	size = 0;
	while (line[idx])
	{
		if (line[idx] == '$')
		{
			env_var = ft_env_var(global, line + idx + 1);
			if (!env_var)
				return (free(new_line), NULL);
			ft_sstrlcpy(new_line + size, env_var, ft_strlen(env_var) + 1);
			size += ft_strlen(env_var);
			idx += ft_envname_len(line + idx + 1) + 1;
		}
		else
		{
			new_line[size] = line[idx];
			size++;
			idx++;
		}
	}
	new_line[size] = 0;
	return (new_line);
}

int	ft_hd_nquote(t_global *global, int fd[2], char *lim)
{
	char	*here_line;
	char	*new_line;
	int		pos;
	int		size_tk;

	pos = 1;
	size_tk = 0;
	if (pipe(fd) == -1)
		return (free(lim), 1);
	while (1)
	{
		here_line = readline("> ");
		if (!here_line)
			return (-1);
		if (ft_strncmp(here_line, lim, ft_strlen(lim)) == 0
			&& here_line[ft_strlen(lim)] == 0)
			break ;
		new_line = ft_hd_parse(global, here_line);
		printf("nl = %s\n", new_line);
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
		return (free(lim), 1);
	while (1)
	{
		here_line = readline("> ");
		if (!here_line)
			return (-1);
		if (ft_strncmp(here_line, lim, ft_strlen(lim)) == 0
			&& here_line[ft_strlen(lim)] == 0)
			break ;
		write_all(fd[1], here_line, ft_strlen(here_line));
		write(fd[1], "\n", 1);
		free(here_line);
	}
	free(lim);
	close(fd[1]);
	global->command->infile = fd[0];
	return (2);
}

int	ft_heredoc(t_global *global, char *line)
{
	char	*lim;
	int		fd[2];
	int		in_quote;

	in_quote = 0;
	lim = ft_getlim(global, line, &in_quote); // protections?
	if (!lim)
		return (-1);
	if (in_quote)
		return (ft_hd_quote(global, fd, lim));
	return (ft_hd_nquote(global, fd, lim));
}
