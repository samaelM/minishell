/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/24 18:50:53 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set && set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_envname_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_in_set(str[i], " 	\"'$"))
		i++;
	return (i);
}
int	ft_env_len(char *str)
{
	int		i;
	char	*env_var;

	i = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(env_var, str, i + 1);
	printf("cette arg env: %s\n", env_var);
	i = ft_strlen(getenv(env_var));
	printf("retourne: %d\n", i);
	free(env_var);
	return (i);
}

char	*ft_get_env(char *str)
{
	int		i;
	char	*env_var;
	char	*content;

	i = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(env_var, str, i + 1);
	content = getenv(env_var);
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
	while (str[i] && !is_in_set(str[i], " 	"))
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
						j += ft_env_len(str + i + 1);
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
		while (str[i] && !is_in_set(str[i], "\"' 	"))
		{
			if (str[i] == '$')
			{
				j += ft_env_len(str + i + 1);
				i += ft_envname_len(str + i + 1);
			}
			else
				j++;
			i++;
		}
	}
	return (j);
}

int	ft_get_arg(char *dest, char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (str[i] && is_in_set(str[i], " 	"))
		i++;
	while (str[i] && !is_in_set(str[i], " 	"))
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
						ft_strlcpy(dest + j, ft_get_env(str + i + 1),
							ft_env_len(str + i + 1) + 1);
						j += ft_env_len(str + i + 1);
						i += ft_envname_len(str + i + 1);
					}
					else
						dest[j++] = str[i];
					i++;
				}
				i++;
			}
			else if (str[i] && str[i] == '\'')
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
		while (str[i] && !is_in_set(str[i], "\"' 	"))
		{
			if (str[i] == '$')
			{
				ft_strlcpy(dest + j, ft_get_env(str + i + 1), ft_env_len(str + i
						+ 1) + 1);
				j += ft_env_len(str + i + 1);
				i += ft_envname_len(str + i + 1);
			}
			else
				dest[j++] = str[i];
			i++;
		}
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
		if (str[i])
			nb_t++;
		while (str[i] && !is_in_set(str[i], " 	"))
		{
			if (str[i] && str[i] == '"')
			{
				i++;
				while (str[i] && str[i] != '"')
				{
					i++; // rajouter une condition si il trouve un anti slash
				}
				i++;
			}
			else if (str[i] && str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
				{
					i++; // rajouter une condition si il trouve un anti slash
				}
				i++;
			}
			else
			{
				while (str[i] && !is_in_set(str[i], "\"' 	"))
					i++;
			}
		}
	}
	return (nb_t);
}

t_command	*ft_token(char *cmd)
{
	t_command	*command;
	int			i;
	int			j;
	int			size;

	j = 0;
	size = ft_counttoken(cmd);
	command = malloc(sizeof(t_command));
	command->args = malloc(sizeof(char *) * (size + 1));
	i = 0;
	while (i < size)
	{
		command->args[i] = malloc(sizeof(char) * (ft_size_token(cmd) + 1));
		j = ft_get_arg(command->args[i], cmd);
		cmd = cmd + j;
		i++;
	}
	command->args[i] = 0;
	return (command);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_command	*cmd;
	int			i;

	line = NULL;
	(void)argc;
	(void)argv;
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
		i = 0;
		printf("\033[1;94mnb_t = %d\n", ft_counttoken(line));
		printf("size t0 = %d\n", ft_size_token(line));
		printf("line:>%s<\n", line);
		cmd = ft_token(line);
		while (cmd->args[i])
		{
			printf("\033[1;94marg %d:>%s<\033[0m\n", i, cmd->args[i]);
			i++;
		}
		cmd->cmd = cmd->args[0];
		cmd->exit_value = 0;
		free(line);
		//
		ft_exec(cmd, envp);
		free(cmd);
	}
}
