/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 14:48:12 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/15 18:34:34 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*dup;

	if(!src)
		return (NULL);
	dup = ft_calloc(ft_strlen(src) + 1, 1);
	if (!dup)
		return (NULL);
	ft_strlcpy(dup, src, ft_strlen(src) + 1);
	return (dup);
}
