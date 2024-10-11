/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:56 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/11 16:09:39 by maemaldo         ###   ########.fr       */
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
	printf("\n\b\b\b\b");
	rl_on_new_line();
	if (wait(NULL) == -1)
		rl_redisplay();
	else
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
	g_sig = signum;
}
void	signal_ctrD(t_global *g)
{
	printf("exit\n");
	int i = 0;
	while (g->env[i])
	{
		free(g->env[i]);
		i++;
	}
	free(g->env);
	exit(g->exit_value);
}