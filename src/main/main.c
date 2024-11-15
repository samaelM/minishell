/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:32:05 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 15:30:41 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_sig = 0;

int	main(int argc, char **argv, char **envp)
{
	t_global	global;

	(void)argv;
	if (argc > 1)
		return (1);
	ft_bzero(&global, sizeof(t_global));
	global.env = create_env(envp);
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (42)
	{
		g_sig = 0;
		global.line = readline("\001\033[1;95m\002Poivre-echelle> \001\033[0m\002");
		if (ft_check_line(&global))
		{
			if (ft_token(global.line, &global) && global.command
				&& ft_redir(&global, global.line))
				ft_exec(&global);
			ft_free_cmd(global.command);
		}
		else
			global.exit_value = 2;
		free(global.line);
	}
	return (0);
}
