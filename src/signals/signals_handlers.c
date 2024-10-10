/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:56 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/10 19:07:37 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int signum)
{
	signal(SIGINT, sigint_handler);
	printf("\r\n");
	rl_on_new_line();
	// rl_replace_line("", 0);
	rl_redisplay();
	(void)signum;
}

void	sigquit_handler(int signum)
{
	ft_printf("\nbye bye!\n");
	signal(SIGQUIT, sigquit_handler);
	(void)signum;
	exit(0);
}

void	signal_ctrD(t_global *g)
{
	printf("exit\n");
	int i = 0;
	while(g->env[i])
	{
		free(g->env[i]);
		i++;
	}
	free(g->env);
	exit(g->exit_value);
}