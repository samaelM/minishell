/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/19 17:59:05 by maemaldo         ###   ########.fr       */
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
					i++; // rajouter une condition si il trouve un anti slash
					j++;
				}
				i++;
			}
			else if (str[i] && str[i] == '\'')
			{
				i++;
				while (str[i] && str[i] != '\'')
				{
					i++; // rajouter une condition si il trouve un anti slash
					j++;
				}
				i++;
			}
		}
		while (str[i] && !is_in_set(str[i], "\"' 	"))
		{
			i++;
			j++;
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

int	main(void)
{
	char		*line;
	int			i;
	t_command	*cmd;

	line = NULL;
	while (42)
	{
		i = 0;
		line = readline("\033[1;95mShell-et-poivre> \033[0m");
		add_history(line);
		printf("nb_t = %d\n", ft_counttoken(line));
		printf("size t0 = %d\n", ft_size_token(line));
		printf("line:>%s<\n", line);
		cmd = ft_token(line);
		while (cmd->args[i])
		{
			printf("arg %d:>%s<\n", i, cmd->args[i]);
			i++;
		}
		free(cmd);
	}
}
