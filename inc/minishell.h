/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:23:02 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/13 14:01:40 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

///////////////////////////////////////////
///				INCLUDES				///
///////////////////////////////////////////

# include "../lib/libft/libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/wait.h>
# include <unistd.h>

///////////////////////////////////////////
///				MACROS					///
///////////////////////////////////////////

# define TRUE 1

///////////////////////////////////////////
///				STRUCTURES				///
///////////////////////////////////////////

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
	int infile;    // fichier d'entree (par defaut stdin)
	char *cmdpath; // path absolue de la commande (/bin/ls)
	char *cmd;     // juste la commande (ls, cat, wc etc)
	// char	*options;
	t_symb symbole; // s'il y a un sumbole (pipe, heredoc etc)
	char **args;    // les argument de la commande (-R, -rf etc)
	int outfile;    // fichier de sortie (par defaut stdout)
}			t_command;

///////////////////////////////////////////
///				PROTOTYPES				///
///////////////////////////////////////////

///				EXECUTION				///

int			ft_exec_cmd(int fd, char *arg, char **envp, char **path);

///				COMPARATOR				///

int			ft_and(void);
int			ft_or(void);

///				PIPES					///

int			ft_pipex(void);

///				TOKENISATION			///

t_command	*ft_token(char *command);

///				BUILT-INS				///

int			ft_cd(void);
int			ft_echo(void);
int			ft_env(void);
int			ft_exit(void);
int			ft_export(void);
int			ft_pwd(void);
int			ft_unset(void);

///				SIGNALS					///
void		sigint_handler(int sig_num);
void		sigquit_handler(int sig_num);

///				OTHER					///
void		ft_watermark(void);

#endif