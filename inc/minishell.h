/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:23:02 by maemaldo          #+#    #+#             */
/*   Updated: 2024/08/21 15:34:49 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../lib/libft/libft.h"
# include "tokenisation.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

# define YO salut

typedef enum s_symbole
{
	NONE,
	PIPE,
	HERE_DOC,
	INFILE,
	OUTFILE,
	AND,
	OR
}			t_symb;

typedef struct s_command
{
	int		infile;		//fichier d'entree (par default 0)
	char	*cmdpath;	//path absolue de la commande (/bin/ls)
	char	*cmd;		//juste la commande (ls, cat, wc etc)
	// char	*options;
	t_symb	symbole;	//s'il y a un sumbole (pipe, heredoc etc)
	char	**args;		//les argument de la commande (-R, -rf etc)
	int		outfile;	//fichier de sortie (par default 1)
}			t_command;

void		ft_watermark(void);
void		sigint_handler(int sig_num);
void		sigquit_handler(int sig_num);

#endif