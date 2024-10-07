/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals_handlers.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 12:47:56 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/04 19:42:45 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	sigint_handler(int signum)
{
	signal(SIGINT, sigint_handler);
	printf("\r\n");
	rl_on_new_line();
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
