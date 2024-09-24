/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/20 19:11:41 by ahenault          #+#    #+#             */
/*   Updated: 2024/09/23 18:02:27 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

int ft_pwd(void)
{
	char buf[PATH_MAX];

 	if (getcwd(buf, PATH_MAX) == NULL) 
	{
		printf("Error pwd\n");
		return (1);
	}
	else
		printf("%s\n", buf);
	return (0);
}