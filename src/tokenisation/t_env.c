/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:09:11 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/18 17:51:35 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/tokenisation.h"

int	ft_envname_len(char *str)
{
	int	idx;

	idx = 0;
	if (*str == '?')
		return (1);
	while (str[idx] && (ft_isalnum(str[idx]) || str[idx] == '_'))
		idx++;
	return (idx);
}

// need protection
int	ft_env_len_bis(t_global *global, char *str)
{
	int		len;
	char	*env_var;
	char	*exit_status;

	if (*str == '?')
	{
		exit_status = ft_itoa(global->exit_value);
		if (!exit_status)
			return (perr(ERR_ALLOC), -1);
		len = ft_strlen(exit_status);
		free(exit_status);
		return (len);
	}
	if ((!ft_isalnum(*str)) || (!str[0]))
		return (1);
	len = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (len + 1));
	if (!env_var)
		return (perr(ERR_ALLOC), -1);
	ft_sstrlcpy(env_var, str, len + 1);
	len = ft_strlen(ft_getenv(global->env, env_var));
	free(env_var);
	return (len);
}

// need protection
char	*ft_env_var(t_global *global, char *str)
{
	int		len;
	char	*env_var;
	char	*content;

	if ((!ft_isalnum(*str)) || (!str[0]))
		return ("$");
	len = ft_envname_len(str);
	env_var = malloc(sizeof(char) * (len + 1));
	if (!env_var)
		return (perr(ERR_ALLOC), NULL);
	ft_sstrlcpy(env_var, str, len + 1);
	content = ft_getenv(global->env, env_var);
	free(env_var);
	return (content);
}
