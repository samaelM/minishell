/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahenault <ahenault@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:23:02 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/08 20:26:43 by ahenault         ###   ########.fr       */
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
# include <fcntl.h>
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
# define HEREDOC_NAME "/tmp/heredoc_poivre"

///////////////////////////////////////////
///				STRUCTURES				///
///////////////////////////////////////////

typedef struct s_command
{
	int infile;    // fichier d'entree (par defaut stdin)
	char *cmdpath; // path absolue de la commande (/bin/ls)
	char *cmd;     // juste la commande (ls, cat, wc etc)
	int					is_pipe;
	int					is_heredoc;
	char **args; // les argument de la commande (-R, -rf etc)
	int outfile; // fichier de sortie (par defaut stdout)
	struct s_command	*next;
}						t_command;

typedef struct s_global
{
	t_command			*command;
	char **env;
	int					exit_value;
}						t_global;

///////////////////////////////////////////
///				PROTOTYPES				///
///////////////////////////////////////////

///				EXECUTION				///

int		ft_exec(t_global *s_global);
void	exec_la_cmd(t_global *g);

///				COMPARATOR				///

int						ft_and(void);
int						ft_or(void);

///				PIPES					///

int						ft_pipex(void);

///				TOKENISATION			///

t_command				*ft_token(char *command);
void					ft_free_cmd(t_command *cmd);
void					ft_printcmd(t_command *cmd);
int						ft_check_pipes(char *str);
int						ft_check_redir(char *str);
int						ft_check_line(char *str);
int						ft_check_line_bis(char *str);
int						ft_error_token(char *str);
int						ft_size_token(char *str);
int						ft_get_arg(char *dest, char *str);
int						ft_redir(t_command *cmd, char *line);

///				BUILT-INS				///

int	ft_cd(t_global *glo);
int	ft_pwd(void);
int	ft_echo(t_command *command);
int	ft_exit(t_global *glob);
int ft_env(t_global *glob);
int ft_export(t_global *glo);
int ft_unset(t_global *glob);

///				ENV						///

char **create_our_env(char **envp);
char *ft_getenv(char **env, char *var);
int find_var_in_env(char **env, char *var);
int change_env_var(t_global *glo, char *var, int line);
void change_env_(t_global *glob);

///				SIGNALS					///
void					sigint_handler(int sig_num);
void					sigquit_handler(int sig_num);

///				OTHER					///
void					ft_watermark(void);

///				UTILS					///
size_t					ft_sstrlcpy(char *dst, const char *src, size_t dstsize);
int						is_in_set(char c, char *set);

#endif