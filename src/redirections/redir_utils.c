/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 15:03:21 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/15 15:10:19 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/minishell.h"

char	*ft_get_file_name(t_global *global, char *line)
{
	char	*name;
	int		name_size;
	int		len;

	len = 0;
	name_size = ft_size_token(global, line + 1);
	if (name_size == -1)
		return (NULL);
	name = ft_calloc(name_size + 1, sizeof(char));
	if (!name)
		return (NULL);
	len = ft_get_arg(global, name, line + 1);
	if (len == -1)
		return (free(name), NULL);
	return (name);
}
