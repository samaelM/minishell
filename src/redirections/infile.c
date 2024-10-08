/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:29:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/07 17:17:02 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_outfile(t_command *cmd, char *line)
{
	int		size;
	int		len;
	char	*name;

	if (cmd->outfile > 1)
		close(cmd->outfile);
	// printf("outfile\n");
	len = 0;
	size = ft_size_token(line + 1);
	name = ft_calloc(size, sizeof(char));
	len = ft_get_arg(name, line + 1);
	cmd->outfile = open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->outfile == -1)
		perror(name);
	free(name);
	return (len + 1);
}
int	ft_outfile2(t_command *cmd, char *line)
{
	int		size;
	int		len;
	char	*name;

	if (cmd->outfile > 1)
		close(cmd->outfile);
	// printf("outfile2\n");
	len = 0;
	size = ft_size_token(line + 2);
	name = ft_calloc(size, sizeof(char));
	len = ft_get_arg(name, line + 2);
	cmd->outfile = open(name, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->outfile == -1)
		perror(name);
	free(name);
	return (len + 2);
}
int	ft_infile(t_command *cmd, char *line)
{
	int		size;
	int		len;
	char	*name;

	if (cmd->infile > 1)
		close(cmd->infile);
	if (cmd->is_heredoc)
	{
		// close(cmd->infile);
		unlink("/tmp/heredoc");
		cmd->is_heredoc = 0;
	}
	// printf("infile\n");
	len = 0;
	size = ft_size_token(line + 1);
	name = ft_calloc(size, sizeof(char));
	len = ft_get_arg(name, line + 1);
	cmd->infile = open(name, O_RDONLY);
	if (cmd->infile == -1)
		perror(name);
	free(name);
	return (len + 1);
}

int	ft_heredoc(t_command *cmd, char *line)
{
	int		len;
	int		size;
	char	*lim;
	char	*buff;
	char	*line2;

	if (cmd->infile > 1)
		close(cmd->infile);
	if (cmd->is_heredoc)
	{
		// close(cmd->infile);
		unlink(HEREDOC_NAME);
	}
	buff = malloc(700 * sizeof(char));
	len = 0;
	size = ft_size_token(line + 2);
	lim = ft_calloc(size, sizeof(char));
	ft_get_arg(lim, line + 2);
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
	// printf("%zd\n",write(cmd->infile, "hello\n", 6));
	printf("%zd\n", read(cmd->infile, buff, 700));
	printf(">%s<\n", buff);
	free(buff);
	cmd->is_heredoc = 1;
	return (len + 2);
}

int	ft_redir(t_command *cmd, char *line)
{
	int i = 0;
	while (line[i])
	{
		// printf("redir: %c %d\n", line[i], i);
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
		// i++;
	}
	return (1);
}