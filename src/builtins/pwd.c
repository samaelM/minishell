/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:11:41 by ahenault          #+#    #+#             */
/*   Updated: 2024/11/15 14:03:21 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int	ft_pwd(void)
{
	char	buf[PATH_MAX];

	if (getcwd(buf, PATH_MAX) == NULL)
	{
		ft_perrorf("pwd: error retrieving current directory\n");
		return (1);
	}
	printf("%s\n", buf);
	return (0);
}
