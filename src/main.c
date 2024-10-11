/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/01 14:32:05 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/11 19:53:08 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

int		g_sig = 0;

#define MAX_CMD_LENGTH 100

char	*ft_find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5) != 0)
		i++;
	if (env[i] && ft_strncmp(env[i], "PATH=", 5) == 0)
		return (env[i] + 5);
	return (NULL);
}

char	*ft_get_cmd_path(char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*res;

	i = 0;
	while (paths && paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (tmp == NULL)
			return (NULL);
		res = ft_strjoin(tmp, cmd);
		if (res == NULL)
			return (NULL);
		free(tmp);
		if (access(res, F_OK) == 0)
			return (res);
		free(res);
		i++;
	}
	if (access(cmd, F_OK) == 0)
		return (cmd);
	return (NULL);
}

int	ft_exec_cmd(int fd, char *arg, char **envp, char **path)
{
	char	**args;
	char	*cmd;

	if (fd != 1)
		return (1);
	args = ft_split(arg, ' ');
	if (args)
	{
		cmd = ft_get_cmd_path(path, args[0]);
		if (cmd)
		{
			execve(cmd, args, envp);
			ft_printf("execve");
			free(cmd);
			exit(EXIT_FAILURE);
		}
		ft_printf("error cmd %s not found\n", args[0]);
	}
	exit(EXIT_FAILURE); // qu'est ce que j'ai foutu????
	return (0);
}

// int	main(int ac, char **av, char **envp)
// {
// 	char	*cmd;
// 	int		status;
// 	pid_t	pid;

// 	// char	**args;
// 	// t_command *oui;
// 	(void)ac;
// 	(void)av;
// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, sigquit_handler);
// 	ft_watermark();
// 	while ((cmd = readline("\033[1;95mShell-et-poivre> \033[0m")) != NULL)
// 	{
// 		add_history(cmd);
// 		// oui = ft_token(cmd);
// 		// printf("%s", oui->cmd);
// 		if (ft_strncmp(cmd, "exit", 4) == 0)
// 		{
// 			free(cmd); // replace with ft_exit
// 			break ;
// 		}
// 		else if (ft_strncmp(cmd, "echo", 4) == 0)
// 		{
// 			printf("%s\n", cmd + 5); // replace with ft_echo
// 			free(cmd);
// 		}
// 		else if (ft_strncmp(cmd, "cd", 2) == 0)
// 		{
// 			chdir(cmd + 3); // replace with ft_cd
// 			free(cmd);
// 		} // mettre d'autre else if pour les autre commandes builtins
// 		else if (*cmd)
// 		{
// 			pid = fork();
// 			if (pid == -1)
// 				printf("fork");
// 			else if (pid == 0)
// 			{
// 				// cmd = ft_strdup("   echo 		a");
// 				ft_exec_cmd(1, cmd, envp, ft_split(ft_find_path(envp), ':'));
// 				free(cmd);
// 			}
// 			else
// 				waitpid(pid, &status, 0);
// 			free(cmd);
// 		}
// 	}
// 	return (0);
// }
int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_command	*cmd;
	t_global	global;

	(void)ac;
	(void)av;
	line = NULL;
	global.env = create_our_env(envp);
		global.exit_value = 102;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (42)
	{
		g_sig = 0;
		line = readline("\033[1;95mpoivre-et-Shell> \033[0m");
		if (line == NULL)
			signal_ctrD(&global);
		if (*line)
			add_history(line);
		if (line && ft_check_line(line))
		{
			cmd = ft_token(line, &global);
			ft_redir(&global, line);
			// ft_printcmd(cmd);
			// global.command = cmd;
			if (cmd->args)
				global.command->cmd = cmd->args[0];
			ft_exec(&global);
			ft_free_cmd(cmd);
		}
		printf("exit status: %d\n", global.exit_value);
		free(line);
	}
	rl_clear_history();
}
