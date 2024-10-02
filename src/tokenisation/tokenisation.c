/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/02 16:16:40 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_redir_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && is_in_set(str[i], "<>"))
	{
		while (str[i] && is_in_set(str[i], "<>"))
			i++;
		while (str[i] && is_in_set(str[i], " 	"))
			i++;
		if (str[i] && str[i] == '"')
		{
			i++;
			while (str[i] && str[i] != '"')
				i++;
			i++;
		}
		if (str[i] && str[i] == '\'')
		{
			i++;
			while (str[i] && str[i] != '\'')
				i++;
			i++;
		}
		while (str[i] && !is_in_set(str[i], " 	|<>\"'"))
			i++;
		while (str[i] && is_in_set(str[i], " 	"))
			i++;
	}
	return (i);
}

int	ft_envname_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_in_set(str[i], " 	\"'$"))
		i++;
	return (i);
}

int	ft_env_len_bis(char *str, int in_quote) // nouvelle
{
	int i;
	char *env_var;

	if ((in_quote && is_in_set(*str, "\" 	")) || (!in_quote && !str[0])
						|| (!in_quote && is_in_set(*str, " 	")))
		return (1);
	if (!in_quote && str[0] == '"')
		return (0);
	i = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (i + 1));
	ft_sstrlcpy(env_var, str, i + 1);
	i = ft_strlen(getenv(env_var));
	free(env_var);
	return (i);
}

char	*ft_env_var(char *str, int in_quote) // nouvelle
{
	int i;
	char *env_var;
	char *content;

	if ((in_quote && is_in_set(*str, "\" 	")) || (!in_quote && !str[0])
						|| (!in_quote && is_in_set(*str, " 	")))
		return ("$");
	if (!in_quote && str[0] == '"')
		return ("");
	i = 0;
	i = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (i + 1));
	ft_sstrlcpy(env_var, str, i + 1);
	content = getenv(env_var);
	free(env_var);
	return (content);
}

int	ft_size_token(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && is_in_set(str[i], " 	"))
		i++;
	while (str[i] && !is_in_set(str[i], " 	|<>"))
	{
		while (str[i] && is_in_set(str[i], "\"'"))
		{
			if (str[i] && str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
				{
					if (str[i] == '$')
					{
						j += ft_env_len_bis(str + i + 1, 1);
						i += ft_envname_len(str + i + 1);
					}
					else
						j++;
					i++;
				}
				i++;
			}
			else if (str[i] && str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
				{
					i++;
					j++;
				}
				i++;
			}
		}
		while (str[i] && !is_in_set(str[i], "\"' 	|<>"))
		{
			if (str[i] == '$')
			{
				j += ft_env_len_bis(str + i + 1, 0);
				i += ft_envname_len(str + i + 1);
			}
			else
				j++;
			i++;
		}
		while (str[i] && is_in_set(str[i], "<>"))
			i += ft_redir_len(str + i);
	}
	return (j);
}

int	ft_get_arg(t_command *command, int idx, char *str)
{
	int		i;
	int		j;
	char	*dest;

	dest = command->args[idx];
	j = 0;
	i = 0;
	while (str[i] && is_in_set(str[i], " 	"))
		i++;
	while (str[i] && !is_in_set(str[i], " 	|"))
	{
		while (str[i] && is_in_set(str[i], "\"'"))
		{
			if (str[i] && str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
				{
					if (str[i] == '$')
					{
						ft_sstrlcpy(dest + j, ft_env_var(str + i + 1, 1),
							ft_env_len_bis(str + i + 1, 1) + 1);
						j += ft_env_len_bis(str + i + 1, 1);
						i += ft_envname_len(str + i + 1);
					}
					else
						dest[j++] = str[i];
					i++;
				}
				i++;
			}
			if (str[i] && str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
				{
					dest[j++] = str[i];
					i++;
				}
				i++;
			}
		}
		while (str[i] && !is_in_set(str[i], "\"' 	|<>"))
		{
			if (str[i] == '$')
			{
				ft_sstrlcpy(dest + j, ft_env_var(str + i + 1, 0),
					ft_env_len_bis(str + i + 1, 0) + 1);
				j += ft_env_len_bis(str + i + 1, 0);
				i += ft_envname_len(str + i + 1);
			}
			else
				dest[j++] = str[i];
			i++;
		}
		while (str[i] && is_in_set(str[i], "<>"))
			i += ft_redir_len(str + i);
	}
	dest[j] = 0;
	return (i);
}

int	ft_counttoken(char *str)
{
	int	i;
	int	nb_t;

	i = 0;
	nb_t = 0;
	while (str[i])
	{
		while (str[i] && is_in_set(str[i], " 	"))
			i++;
		if (is_in_set(str[i], "<>"))
			i += ft_redir_len(str + i);
		if (str[i] == '|')
			return (nb_t);
		if (str[i])
			nb_t++;
		while (str[i] && !is_in_set(str[i], " 	"))
		{
			if (str[i] && str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
					i++;
				i++;
			}
			if (str[i] && str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
					i++;
				i++;
			}
			if (str[i] && str[i] == '|')
				return (nb_t);
			while (str[i] && !is_in_set(str[i], "\"' 	|"))
				i++;
		}
	}
	return (nb_t);
}

t_command	*ft_token(char *cmd)
{
	t_command	*command;
	t_command	*tmp;
	int			i;
	int			j;
	int			size;

	j = 0;
	command = ft_calloc(1, sizeof(t_command));
	tmp = command;
	while (*cmd)
	{
		size = ft_counttoken(cmd);
		// printf("nb_t = %d\n", size);
		tmp->args = ft_calloc((size + 1), sizeof(char *));
		i = 0;
		while (i < size)
		{
			tmp->args[i] = ft_calloc((ft_size_token(cmd) + 1), sizeof(char));
			j = ft_get_arg(tmp, i, cmd);
			cmd = cmd + j;
			i++;
		}
		tmp->args[i] = 0;
		while (*cmd && is_in_set(*cmd, " 	"))
			cmd++;
		if (*cmd && is_in_set(*cmd, "<>"))
			cmd += ft_redir_len(cmd);
		if (*cmd && *cmd == '|')
			cmd++;
		if (*cmd)
		{
			printf("new cmd: %s\n", cmd);
			// ft_printcmd(tmp);
			// sleep(2);
			tmp->next = ft_calloc(1, sizeof(t_command));
			tmp = tmp->next;
		}
	}
	return (command);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	t_command	*cmd;

	line = NULL;
	(void)ac;
	(void)av;
	(void)envp;
	while (42)
	{
		line = readline("\033[1;95mShell-et-poivre> \033[0m");
		add_history(line);
		// while (envp[i])
		// 	printf("%s\n", envp[i++]);
		// printf("env var len: %d\n",ft_size_env_var(line, envp));
		// printf("getenv: %s\n", getenv(line));
		// printf("getenvlen: %zu\n", ft_strlen(getenv(line)));
		// printf("getenvlen2: %d\n", ft_env_len(line));
		// printf("nb_t = %d\n", ft_counttoken(line));
		// printf("size t0 = %d\n", ft_size_token(line));
		// printf("DEBUG: line:>%s<\n", line);
		if (ft_check_line_bis(line))
		{
			cmd = ft_token(line);
			ft_printcmd(cmd);
			// free(cmd->args);
			ft_free_cmd(cmd);
		}
		free(line);
	}
	rl_clear_history();
}
