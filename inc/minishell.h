/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:23:02 by maemaldo          #+#    #+#             */
/*   Updated: 2024/09/30 19:24:18 by ahenault         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

///////////////////////////////////////////
///				INCLUDES				///
///////////////////////////////////////////

# include "../lib/libft/libft.h"
# include <errno.h>
# include <linux/limits.h>
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
# define METACHAR " 	|<>"

///////////////////////////////////////////
///				STRUCTURES				///
///////////////////////////////////////////

typedef struct s_command
{
	char *infile;  // fichier d'entree (par defaut stdin)
	char *cmdpath; // path absolue de la commande (/bin/ls)
	char *cmd;     // juste la commande (ls, cat, wc etc)
	char **args;   // les argument de la commande (-R, -rf etc)
	char *outfile; // fichier de sortie (par defaut stdout)
	struct s_command	*next;
}						t_command;

typedef struct s_global
{
	t_command			*command;
	t_list				*env_list;
	int					exit_value;
}						t_global;

///////////////////////////////////////////
///				PROTOTYPES				///
///////////////////////////////////////////

///				EXECUTION				///

int						ft_exec_cmd(int fd, char *arg, char **envp,
							char **path);
int						ft_exec(t_global *s_global);

///				COMPARATOR				///

int						ft_and(void);
int						ft_or(void);

///				PIPES					///

int						ft_pipex(void);

///				TOKENISATION			///

t_command				*ft_token(char *command);

///				BUILT-INS				///

int						ft_cd(t_command *command);
int						ft_pwd(void);
int						ft_echo(t_command *command);
int						ft_exit(t_global *glob);
int						ft_env(t_command *command, t_list *env_list);

int						ft_export(t_command *command, t_list *env_list);
int						ft_unset(t_command *command, t_list *env_list);

t_list					*create_our_env(char **envp);
t_list					*find_var_in_env(t_list *env_list, char *var);

///				SIGNALS					///
void					sigint_handler(int sig_num);
void					sigquit_handler(int sig_num);

///				OTHER					///
void					ft_watermark(void);

#endif