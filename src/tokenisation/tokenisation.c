/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:18 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/16 18:21:18 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

// static char	**ft_clear(char **str)
// {
// 	int		i;
// 	char	*tmp;

// 	i = 0;
// 	while (str && str[i])
// 	{
// 		tmp = str[i];
// 		str[i] = ft_strtrimtoken(str[i]);
// 		free(tmp);
// 		if (!str[i])
// 			return (ft_free_tab(str), NULL);
// 		i++;
// 	}
// 	return (str);
// }

// static int	ft_countwords(const char *s, char c)
// {
// 	int	i;
// 	int	nb;
// 	int	in_quote;

// 	nb = 0;
// 	i = 0;
// 	in_quote = 0;
// 	while (s[i])
// 	{
// 		if (s[i] == '"' || s[i] == '\'')
// 			in_quote = !in_quote;
// 		if (!in_quote && (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0')))
// 			nb++;
// 		i++;
// 	}
// 	return (nb);
// }

// static int	ft_wordsize(const char *s, char c)
// {
// 	int	i;

// 	i = 0;
// 	if (s[i] == '"' || s[i] == '\'')
// 	{
// 		if (s[i + 1] == '\0')
// 			return (1);
// 		i++;
// 		while (s[i] && (s[i] != '"' && s[i] != '\''))
// 			i++;
// 		return (i + 1);
// 	}
// 	while (s[i] && (s[i] != c && s[i] != '"' && s[i] != '\''))
// 		i++;
// 	return (i);
// }

// static char	**ft_malloc_tab(char const *s, char c)
// {
// 	char	**tab;
// 	int		size;

// 	if (!s)
// 		return (NULL);
// 	size = ft_countwords(s, c) + 1;
// 	size = 10;
// 	tab = (char **)malloc(sizeof(char *) * size);
// 	if (!tab)
// 		return (NULL);
// 	return (tab);
// }

// char	**ft_token(char const *s, char c)
// {
// 	char	**tab;
// 	int		i;
// 	int		j;

// 	tab = ft_malloc_tab(s, c);
// 	if (!tab)
// 		return (0);
// 	i = 0;
// 	j = 0;
// 	while (s[i])
// 	{
// 		if (s[i] != c)
// 		{
// 			tab[j] = (char *)malloc(sizeof(char) * (ft_wordsize(&s[i], c) + 1));
// 			if (!tab[j])
// 				return (ft_free_tab(tab), NULL);
// 			ft_strlcpy(tab[j], (char *)&s[i], ft_wordsize(&s[i], c) + 1);
// 			i = i + ft_wordsize(&s[i], c);
// 			j++;
// 		}
// 		else
// 			i++;
// 	}
// 	tab[j] = NULL;
// 	return (ft_clear(tab));
// }


int	is_in_set(char c, char *set)
{
	int	i;

	i = 0;
	while (set[i])
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}
int	size_arguments(char *cmd)
{
	int	size;
	int	idx;

	size = 0;
	idx = 0;
	while (cmd[idx] && is_in_set(cmd[idx], " 	"))
		idx++;
	return (1);
}

char	*ft_get_arguments(char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i] && is_in_set(cmd[i], " 	"))
		i++;
	return (cmd);
}

t_command	*ft_token(char *cmd)
{
	t_command	*token_cmd;
	int			i;
	int			j;

	token_cmd = malloc(sizeof(t_command));
	i = 0;
	j = 0;
	while (cmd[i] && is_in_set(cmd[i], " 	"))
		i++;
	j = i;
	while (cmd[i] && ft_isalnum(cmd[i]))
		i++;
	token_cmd->cmd = malloc(i - j + 2);
	ft_strlcpy(token_cmd->cmd, cmd + j, i - j +1);
	return (token_cmd);
}
// int main(void)
// {
// 	char *line =NULL;
// 	t_command *cmd;
// 	while (42)
// 	{
// 		line = get_next_line(STDIN_FILENO);
// 		printf("line:>%s<\n", line);
// 		cmd = ft_token(line);
// 		printf("cmd:>%s<\n", cmd->cmd);
// 	}
// }