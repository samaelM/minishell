/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:32:05 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/30 19:40:19 by maemaldo         ###   ########.fr       */
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
	char		*line;
	t_global	global;

	(void)argc;
	(void)argv;
	ft_bzero(&global, sizeof(t_global));
	global.env = create_our_env(envp);
	global.exit_value = 0;
	global.exit_value = g_sig;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (42)
	{
		g_sig = 0;
		line = readline("\001\033[1;95m\002Poivre-echelle> \001\033[0m\002");
		if (g_sig == SIGINT)
			global.exit_value = 130;
		if (line == NULL)
			signal_ctrD(&global);
		if (*line)
			add_history(line);
		if (line && ft_check_line(line))
		{
			// printf("step 1\n");
			if (ft_token(line, &global) && ft_redir(&global, line))
				ft_exec(&global);
			// ft_readfile(global.command->infile);
			// ft_printcmd(global.command);
			ft_free_cmd(global.command);
		}
		// printf("\033[0;33mexit status: %d\n", global.exit_value);
		free(line);
	}
}
