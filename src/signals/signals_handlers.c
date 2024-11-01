/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:56 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/01 16:38:00 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int signum)
{
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	if (wait(NULL) == -1)
		rl_redisplay();
	g_sig = signum;
}

void	sigquit_handler(int signum)
{
	rl_on_new_line();
	if (wait(NULL) == -1)
	{
		printf("\e[2K\r");
		rl_redisplay();
	}
	else
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_sig = signum;
}

void	signal_ctrd(t_global *g)
{
	int	i;

	printf("exit\n");
	i = 0;
	while (g->env[i])
		free(g->env[i++]);
	free(g->env);
	rl_clear_history();
	exit(g->exit_value);
}
