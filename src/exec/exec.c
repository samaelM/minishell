/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 17:36:18 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/11 17:39:42 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_waitall(t_global *global)
{
	while (wait(&global->exit_value) != -1)
		;
	// printf("exec status: %d\n", global->exit_value);
	if (WIFEXITED(global->exit_value))
	{
		global->exit_value = WEXITSTATUS(global->exit_value);
	}
	else
	{
		global->exit_value = 128 + g_sig;
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
	{
		g->exit_value = exec_one_cmd(g);
		return (g->exit_value);
	}
	exec_pipe_cmds(g);
	return (0);
}
