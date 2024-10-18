/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/02 19:52:21 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/18 17:59:07 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENISATION_H
# define TOKENISATION_H

# include "minishell.h"

int		ft_envname_len(char *str);
int		ft_env_len_bis(t_global *global, char *str);
char	*ft_env_var(t_global *global, char *str);
int		ft_redir_len(char *str);

#endif