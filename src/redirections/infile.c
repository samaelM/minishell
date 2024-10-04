/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   infile.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/04 13:29:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/04 16:36:25 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"
#include <fcntl.h>

int	ft_outfile(t_command *cmd, char *line)
{
	int		size;
	int		i;
	char	*name;

	i = 0;
	size = ft_size_token(line + 1);
	name = ft_calloc(size, sizeof(char));
	i = ft_get_arg(name, line + 1);
	cmd->outfile = open(name, O_CREAT | O_TRUNC | O_RDWR, 0666);
	if (cmd->outfile == -1)
		perror(name);
	free(name);
	return (i + 1);
}
int	ft_outfile2(t_command *cmd, char *line)
{
	int		size;
	int		i;
	char	*name;

	i = 0;
	size = ft_size_token(line + 2);
	name = ft_calloc(size, sizeof(char));
	i = ft_get_arg(name, line + 2);
	cmd->outfile = open(name, O_CREAT | O_APPEND | O_RDWR, 0666);
	if (cmd->outfile == -1)
		perror(name);
	free(name);
	return (i + 2);
}
int	ft_infile(t_command *cmd, char *line)
{
	int		size;
	int		i;
	char	*name;

	i = 0;
	size = ft_size_token(line + 1);
	name = ft_calloc(size, sizeof(char));
	i = ft_get_arg(name, line + 1);
	cmd->infile = open(name, O_RDONLY);
	if (cmd->infile == -1)
		perror(name);
	free(name);
	return (i + 1);
}

int	ft_redir(t_command *cmd, char *line)
{
	int i = 0;
	while (line[i])
	{
		if (ft_strncmp(line + i, ">>", 2) == 0)
			i += ft_outfile2(cmd, line + i);
		else if (line[i] == '>')
			i += ft_outfile(cmd, line + i);
		else if (ft_strncmp(line + i, "<<", 2) == 0)
			i += 2;
		else if (line[i] == '<')
			i += ft_infile(cmd, line + i);
		while (line[i] && !is_in_set(line[i], "><|"))
			i++;
		if (line[i] == '|')
			cmd = cmd->next;
		i++;
	}
	return (1);
}