/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/27 14:32:02 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

size_t	ft_sstrlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	i;

	i = 0;
	while (src && src[i] && i + 1 < dstsize)
	{
		dst[i] = src[i];
		i++;
	}
	if (dstsize > 0)
	{
		dst[i] = '\0';
		i++;
	}
	return (ft_strlen(src));
}

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

// int	ft_env_len(char *str)
// {
// 	int		i;
// 	char	*env_var;

// 	i = ft_envname_len(str);
// 	env_var = malloc(sizeof(char) * (i + 1));
// 	ft_sstrlcpy(env_var, str, i + 1);
// 	i = ft_strlen(getenv(env_var));
// 	free(env_var);
// 	return (i);
// }

// char	*ft_get_env(char *str)
// {
// 	int		i;
// 	char	*env_var;
// 	char	*content;

// 	i = ft_envname_len(str);
// 	env_var = malloc(sizeof(char) * (i + 1));
// 	ft_sstrlcpy(env_var, str, i + 1);
// 	content = getenv(env_var);
// 	free(env_var);
// 	return (content);
// }

int	ft_env_len_bis(char *str, int in_quote) // nouvelle
{
	int		i;
	char	*env_var;

	if ((in_quote && is_in_set(*str, "\" 	")) || (!in_quote && !str[0]))
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

	if ((in_quote && is_in_set(*str, "\" 	")) || (!in_quote && !str[0]))
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
		while (str[i] && !is_in_set(str[i], "\"' 	|"))
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
		while (str[i] && !is_in_set(str[i], "\"' 	|"))
		{
			if (str[i] == '$')
			{
				ft_sstrlcpy(dest + j, ft_env_var(str + i + 1, 0), ft_env_len_bis(str
						+ i + 1, 0) + 1);
				j += ft_env_len_bis(str + i + 1, 0);
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
			// retire les espaces/tabs du debut
			i++;
		if (str[i] == '|')
			return (nb_t);
		if (str[i]) // si on est pas arriver a la fin,
			// alors nb token++
			nb_t++;
		while (str[i] && !is_in_set(str[i], " 	"))
		// tant qu'il ya pas de separateur
		{
			if (str[i] && str[i] == '"') // si dquote
			{
				i++;
				while (str[i] && str[i] != '"')
					// jusqu'a la fermeture du dquote
					i++;
				i++;
			}
			else if (str[i] && str[i] == '\'') // si quote
			{
				i++;
				while (str[i] && str[i] != '\'')
					// jusqu'a la fermeture du quote
					i++;
				i++;
			}
			else if (str[i] && str[i] == '|')
				return (nb_t);
			else
			{
				while (str[i] && !is_in_set(str[i], "\"' 	|"))
					i++;
			}
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
			// faire en sorte que cq retire que 1 pipe
			cmd++;
		if (*cmd && *cmd == '|')
			cmd++;
		if (*cmd)
		{
			printf("new cmd\n");
			tmp->next = ft_calloc(1, sizeof(t_command));
			tmp = tmp->next;
		}
	}
	return (command);
}

int	main(int ac, char **av, char **envp)
{
	char		*line;
	int			i;
	int			j;
	t_command	*cmd;

	line = NULL;
	(void)ac;
	(void)av;
	// (void)cmd;
	(void)envp;
	while (42)
	{
		i = 0;
		j = 0;
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
		printf("line:>%s<\n", line);
		cmd = ft_token(line);
		while (cmd)
		{
			i = 0;
			printf("-----\ncmd[%d]\n", j++);
			while (cmd->args && cmd->args[i])
			{
				printf("arg[%d]:>%s<\n", i, cmd->args[i]);
				free(cmd->args[i]);
				i++;
			}
			cmd = cmd->next;
		}
		printf("-----\n");
		// free(cmd->args);
		free(cmd);
		free(line);
	}
	rl_clear_history();
}
