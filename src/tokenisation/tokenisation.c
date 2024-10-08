/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/07 17:05:41 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

void	ft_free_cmd(t_command *cmd)
{
	int			i;
	t_command	*tmp;

	while (cmd)
	{
		i = 0;
		while (cmd->args && cmd->args[i])
		{
			free(cmd->args[i]);
			i++;
		}
		tmp = cmd;
		cmd = cmd->next;
		free(cmd);
	}
}

void	ft_printcmd(t_command *cmd)
{
	int	i;
	int	j;

	j = 0;
	while (cmd)
	{
		i = 0;
		// printf("-----\ncmd[%d]\n", j++);
		while (cmd->args && cmd->args[i])
		{
			// printf("arg[%d]:>%s<\n", i, cmd->args[i]);
			// free(cmd->args[i]);
			i++;
		}
		cmd = cmd->next;
	}
	// printf("-----\n");
}

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

int	ft_check_pipes(char *str)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (is_in_set(str[i], " 	"))
		i++;
	if (str[i] == '|')
		return (i);
	while (str[i])
	{
		if (str[i] == '|')
		{
			j = i;
			i++;
			while (is_in_set(str[i], " 	"))
				i++;
			if (!str[i] || str[i] == '|')
				return (j);
		}
		i++;
	}
	return (-1);
}

int	ft_check_redir(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strncmp(str + i, ">>", 2) == 0)
		{
			// printf(">>\n");
			i++;
		}
		else if (str[i] == '>')
		{
			// printf(">\n");
		}
		if (ft_strncmp(str + i, "<<", 2) == 0)
		{
			// printf("<<\n");
			i++;
		}
		else if (str[i] == '<')
		{
			// printf("<\n");
		}
		i++;
	}
	return (-1);
}

int	ft_check_line(char *str)
{
	if (ft_check_pipes(str) > -1)
	{
		// printf("syntax error near unexpected token `%c'\n",
		//	str[ft_check_pipes(str)]);
		return (0);
	}
	ft_check_redir(str);
	return (1);
}

int	ft_redir_len(char *str)
{
	int	i;

	i = 0;
	while (str[i] && !is_in_set(str[i], " 	|"))
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
		while (str[i] && !is_in_set(str[i], " 	|<>"))
			i++;
	}
	while (str[i] && is_in_set(str[i], " 	"))
		i++;
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
			// retire les espaces/tabs du debut
			i++;
		while (is_in_set(str[i], "|><"))
		{
			if (str[i] == '|')
				return (nb_t);
			if (is_in_set(str[i], "<>"))
				i += ft_redir_len(str + i);
			while (str[i] && is_in_set(str[i], " 	"))
				// retire les espaces/tabs du debut
				i++;
		}
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
			if (str[i] && str[i] == '\'') // si quote
			{
				i++;
				while (str[i] && str[i] != '\'')
					// jusqu'a la fermeture du quote
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
		if (*cmd && *cmd == '|')
			cmd++;
		if (*cmd && is_in_set(*cmd, "<>"))
			cmd += ft_redir_len(cmd);
		if (*cmd)
		{
			// printf("new cmd: %s\n", cmd);
			// ft_printcmd(tmp);
			// sleep(2);
			tmp->next = ft_calloc(1, sizeof(t_command));
			tmp = tmp->next;
		}
	}
	return (command);
}

int	main(int argc, char **argv, char **envp)
{
	char		*line;
	t_command	*cmd;
	int			i;
	t_global	global;

	line = NULL;
	(void)argc;
	(void)argv;
	(void)envp;
	global.env = create_our_env(envp);
	global.exit_value = 0;
	while (42)
	{
		line = readline("\033[1;95mShell-et-poivre> \033[0m");
		add_history(line);
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
		global.command = cmd;
		//
		ft_exec(&global);
		//
		// if (ft_check_line(line))
		// {
		// 	cmd = ft_token(line);
		// 	ft_printcmd(cmd);
		// 	// free(cmd->args);
		ft_free_cmd(cmd);
		// 	// lstclear
		// }
		free(line);
	}
	// rl_clear_history();
}
