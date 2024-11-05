/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:11:46 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/05 17:23:53 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

static int	skip_cmd(char *line)
{
	int	i;

	i = 0;
	// printf("coucou?\n");
	while (line[i] && line[i] != '|')
		i++;
	// printf("skip = %i (%s)\n", i, line + i);
	return (i);
}
// #include <time.h>

static int	skip_nonredir(t_global *global, char *line, int i)
{
	int	skipped;

	skipped = 0;
	while (line[i + skipped] && !is_in_set(line[i + skipped], "><|"))
	{
		// printf("jspskip: %d, %s\n", i + skipped, line + i + skipped);
		// sleep(1);
		if (!is_in_set(line[i + skipped], "'\""))
			skipped++;
		skipped += ft_skipquotes(line + i + skipped, '"');
		skipped += ft_skipquotes(line + i + skipped, '\'');
		if (line[i + skipped] == '|')
		{
			skipped++;
			global->tmp = global->tmp->next;
		}
	}
	return (skipped);
}

int	ft_redir(t_global *global, char *line)
{
	int	i;
	int	tmp;

	if (!global->command)
		return (0);
	global->tmp = global->command;
	i = 0;
	tmp = 0;
	while (line[i])
	{
		if (ft_strncmp(line + i, ">>", 2) == 0)
			tmp = ft_outfile2(global, line + i);
		else if (line[i] == '>')
			tmp = ft_outfile(global, line + i);
		else if (ft_strncmp(line + i, "<<", 2) == 0)
			tmp = ft_heredoc(global, line + i);
		else if (line[i] == '<')
			tmp = ft_infile(global, line + i);
		// printf("avant if: %d\n", i);
		if (tmp < 0)
			i += skip_cmd(line + i);
		if (!line[i])
			return (1);
		i += tmp;
		// printf("jspredir: %d, %s\n", i, line + i);
		i += skip_nonredir(global, line, i);
	}
	// printf("fin redir\n");
	return (1);
}

// echo hi | cat <"./test_files/infile"