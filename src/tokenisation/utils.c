/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:40:51 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/08 18:07:04 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

/*				cmd manipulation				*/
void	ft_free_cmd(t_command *cmd)
{
	int			i;
	t_command	*tmp;

	while (cmd)
	{
		i = 0;
		if (cmd->infile != 0 && cmd->infile != 1 && cmd->infile != 2)
			close(cmd->infile);
		if (cmd->is_heredoc)
			unlink(HEREDOC_NAME);
		if (cmd->outfile != 0 && cmd->outfile != 1 && cmd->outfile != 2)
			close(cmd->outfile);
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	ft_printcmd(t_command *cmd)
{
	int	i;
	int	j;

	j = 0;
	while (cmd)
	{
		i = 0;
		printf("-----\ncmd[%d]\n", j++);
		printf("infile fd=%d\n", cmd->infile);
		while (cmd->args && cmd->args[i])
		{
			printf("arg[%d]:>%s<\n", i, cmd->args[i]);
			// free(cmd->args[i]);
			i++;
		}
		printf("outfile fd=%d\n", cmd->outfile);
		cmd = cmd->next;
	}
	printf("-----\n");
}
/*												*/

size_t	ft_sstrlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	if (!dst)
		return (0);
	while (src && src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
	{
		dst[i] = '\0';
		i++;
	}
	return (ft_strlen(src));
}

int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_error_token(char *str)
{
	printf("syntax error near unexpected token `%s'\n", str);
	if (str)
		free(str);
	return (-1);
}