/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/08 18:39:43 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_skipquotes(char *str, char q)
{
	int	i;

	i = 0;
	if (str[i] && str[i] == q)
	{
		i++;
		while (str[i] && str[i] != q)
			i++;
		i++;
	}
	return (i);
}

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
	while (str[i] && ft_isalnum(str[i]))
		i++;
	return (i);
}

//	calcule la taille de la var finale
int	ft_env_len_bis(char *str, int in_quote)
{
	int		i;
	char	*env_var;

	(void)in_quote;
	if ((!ft_isalnum(*str)) || (!str[0]))
		return (1);
	i = ft_envname_len(str);
	// env_var = NULL;
	env_var = malloc(sizeof(char) * (i + 1));
	if (!env_var)
		return (0);
	ft_sstrlcpy(env_var, str, i + 1);
	i = ft_strlen(getenv(env_var));
	free(env_var);
	return (i);
}

char	*ft_env_var(char *str, int in_quote)
{
	int		i;
	char	*env_var;
	char	*content;

	(void)in_quote;
	if ((!ft_isalnum(*str)) || (!str[0]))
		return ("$");
	i = 0;
	i = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (i + 1));
	// env_var = NULL;
	if (!env_var)
		return (NULL);
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
			if (str[i] && str[i] == '\'')
				j += ft_skipquotes(str + i, '\'') - 2;
			i += ft_skipquotes(str + i, '\'');
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

int	ft_get_arg(char *dest, char *str)
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
			i += ft_skipquotes(str + i, '"');
			i += ft_skipquotes(str + i, '\'');
			if (str[i] && str[i] == '|')
				return (nb_t);
			while (str[i] && !is_in_set(str[i], "\"' 	|"))
				i++;
		}
	}
	return (nb_t);
}

int	ft_set_args(char **args, char **cmd, int *j, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
	//	printf("size=%d\n", ft_size_token(*cmd));
		args[i] = ft_calloc((ft_size_token(*cmd) + 1), sizeof(char));
		*j = ft_get_arg(args[i], *cmd);
		*cmd = *cmd + *j;
		i++;
	}
	args[i] = 0;
	return (1);
}

t_command	*ft_token(char *cmd)
{
	t_command	*command;
	t_command	*tmp;
	int			j;
	int			size;

	j = 0;
	command = ft_calloc(1, sizeof(t_command));
	tmp = command;
	while (*cmd)
	{
		size = ft_counttoken(cmd);
		tmp->args = ft_calloc((size + 1), sizeof(char *));
		ft_set_args(tmp->args, &cmd, &j, size);
		while (*cmd && is_in_set(*cmd, " 	"))
			cmd++;
		if (*cmd && is_in_set(*cmd, "<>"))
			cmd += ft_redir_len(cmd);
		if (*cmd && *cmd == '|')
			cmd++;
		if (*cmd)
		{
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
	t_global	global;

	(void)argc;
	(void)argv;
	line = NULL;
	global.env = create_our_env(envp);
	global.exit_value = 0;
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	while (42)
	{
		line = readline("\033[1;95mPoivre-et-Shell> \033[0m");
		add_history(line);
		if (line && ft_check_line_bis(line))
		{
			cmd = ft_token(line);
			ft_redir(cmd, line);
			global.command = cmd;
			if(cmd->args)
				global.command->cmd = cmd->args[0];
			ft_exec(&global);
			ft_printcmd(cmd);
			ft_free_cmd(cmd);
		}
		free(line);
	}
}
