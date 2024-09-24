/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 18:49:59 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/24 18:57:28 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_env(t_command *command, char **envp)
{
	(void)command;
	while (*envp)
	{
 		printf("%s\n", *envp);
 		envp++;
	}
	return (0);
}