/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:32:05 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/15 13:17:43 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_sig = 0;

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_global	global;

	(void)ac;
	(void)av;
	global.env = create_our_env(envp);
	global.exit_value = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (42)
	{
		g_sig = 0;
		line = readline("\033[1;95mPoivre-echelle> \033[0m");
		if (line == NULL)
			signal_ctrD(&global);
		if (*line)
			add_history(line);
		if (line && ft_check_line(line))
		{
			ft_token(line, &global);
			ft_redir(&global, line);
			// ft_printcmd(global.command);
			ft_exec(&global);
			ft_free_cmd(global.command);
		}
		// printf("exit status: %d\n", global.exit_value);
		free(line);
	}
}
