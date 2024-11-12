/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/02 14:40:51 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/12 19:56:53 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_glob(t_global *glob)
{
	free_tab(glob->env);
	ft_free_cmd(glob->command);
	free(glob->line);
}

void	ft_free_cmd(t_command *cmd)
{
	int			i;
	t_command	*tmp;

	while (cmd)
	{
		i = 0;
		if (cmd->infile > 2)
			close(cmd->infile);
		if (cmd->outfile > 2)
			close(cmd->outfile);
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		if (cmd->args)
			free(cmd->args);
		tmp = cmd;
		cmd = cmd->next;
		free(tmp);
	}
}

void	free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return ;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
			printf("\033[1;94marg[%d]:>%s<\033[0m\n", i, cmd->args[i]);
			i++;
		}
		printf("outfile fd=%d\n", cmd->outfile);
		cmd = cmd->next;
	}
	printf("-----\n");
}

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
