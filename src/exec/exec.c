/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/11 19:08:12 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_waitall(t_global *g)
{
	while (wait(&g->exit_value) != -1)
		;
	// printf("exec status: %d\n", g->exit_value);
	if (WIFEXITED(g->exit_value))
	{
		g->exit_value = WEXITSTATUS(g->exit_value);
	}
	else
	{
		g->exit_value = 128 + g_sig;
	}
}

int	check_is_cmd_is_ok(t_global *g)
{
	if (g->command && g->command->args && g->command->args[0])
	{
		change_env_(g);
		if (g->command->infile != -2 && g->command->outfile != -2)
			return (0);
	}
	return (1);
}

int	ft_exec(t_global *g)
{
	if (g->command->next == NULL)
		return (exec_one_cmd(g));
	exec_pipe_cmds(g);
	return (0);
}
