/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/10 16:14:22 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_envname_len(char *str)
{
	int	idx;

	idx = 0;
	while (str[idx] && ft_isalnum(str[idx]))
		idx++;
	return (idx);
}

// need protection
int	ft_env_len_bis(char *str)
{
	int		idx;
	char	*env_var;

	if ((!ft_isalnum(*str)) || (!str[0]))
		return (1);
	idx = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (idx + 1));
	if (!env_var)
		return (perr(ERR_ALLOC), -1);
	ft_sstrlcpy(env_var, str, idx + 1);
	idx = ft_strlen(getenv(env_var));
	free(env_var);
	return (idx);
}

// need protection
char	*ft_env_var(char *str)
{
	int		idx;
	char	*env_var;
	char	*content;

	if ((!ft_isalnum(*str)) || (!str[0]))
		return ("$");
	idx = 0;
	idx = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (idx + 1));
	if (!env_var)
		return (perr(ERR_ALLOC), NULL);
	ft_sstrlcpy(env_var, str, idx + 1);
	content = getenv(env_var);
	free(env_var);
	return (content);
}
