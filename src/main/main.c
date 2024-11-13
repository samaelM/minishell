/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:32:05 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/13 16:07:57 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	g_sig = 0;

int	ft_readfile(int fd)
{
	char	*line;

	if (fd < 3)
		return (0);
	while (42)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		printf("%s", line);
		free(line);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_global	global;

	(void)argv;
	if (argc > 1)
		return (1);
	ft_bzero(&global, sizeof(t_global));
	global.env = create_our_env(envp);
	global.exit_value = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (42)
	{
		g_sig = 0;
		global.line = readline("\001\033[1;95m\002Poivre-echelle> \001\033[0m\002");
		if (g_sig == SIGINT)
			global.exit_value = 130;
		if (global.line == NULL)
			signal_ctrd(&global);
		if (*global.line)
			add_history(global.line);
		if (global.line && ft_check_line(global.line))
		{
			if (ft_token(global.line, &global) && global.command
				&& ft_redir(&global, global.line))
			{
				g_sig = 0;
				// ft_printcmd(global.command);
				ft_exec(&global);
			}
			ft_free_cmd(global.command);
		}
		else
			global.exit_value = 2;
		// printf("\033[0;33mexit status: %d\n", global.exit_value);
		free(global.line);
	}
	return (0);
}
