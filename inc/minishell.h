/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:23:02 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/15 13:14:29 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

///////////////////////////////////////////
///				INCLUDES				///
///////////////////////////////////////////

# include "../lib/libft/libft.h"
# include <errno.h>
# include <fcntl.h>
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
# define HEREDOC_NAME "/tmp/heredoc_poivre"
# define ERR_ALLOC \
	"an error has occured\
, it may be related with \
a malloc failure"

///////////////////////////////////////////
///				STRUCTURES				///
///////////////////////////////////////////

typedef struct s_command
{
	int					infile;
	char				*cmdpath;
	char				*cmd;
	int					is_pipe;
	int					is_heredoc;
	char				**args;
	int					outfile;
	struct s_command	*next;
}						t_command;

typedef struct s_global
{
	t_command			*command;
	t_command			*tmp;
	char				**env;
	int					exit_value;
}						t_global;

///////////////////////////////////////////
///				PROTOTYPES				///
///////////////////////////////////////////

///				EXECUTION				///

int						ft_exec(t_global *s_global);
void					exec_la_cmd(t_global *g);

///				COMPARATOR				///

int						ft_and(void);
int						ft_or(void);

///				PIPES					///

int						ft_pipex(void);

///				TOKENISATION			///

t_command				*ft_token(char *command, t_global *global);
void					ft_free_cmd(t_command *cmd);
void					ft_printcmd(t_command *cmd);
int						ft_check_line(char *str);
int						ft_size_token(t_global *global, char *str);
int						ft_get_arg(t_global *global, char *dest, char *str);
int						ft_envname_len(char *str);
int						ft_env_len_bis(t_global *global, char *str);
char					*ft_env_var(t_global *global, char *str);
int						ft_skipquotes(char *str, char quote);
int						ft_redir_len(char *str);

///				REDIRECTION				///

int						ft_redir(t_global *global, char *line);
int						ft_heredoc(t_global *global, char *line);
int						ft_infile(t_global *global, char *line);
int						ft_outfile(t_global *global, char *line);
int						ft_outfile2(t_global *global, char *line);

///				BUILT-INS				///

int						ft_cd(t_global *glo);
int						ft_pwd(void);
int						ft_echo(t_command *command);
int						ft_exit(t_global *glob);
int						ft_env(t_global *glob);
int						ft_export(t_global *glo);
int						ft_unset(t_global *glob);

///				ENV						///

char *ft_var_name(char *var);
int add_env_var(t_global *glo, char *var);
char					**create_our_env(char **envp);
char					*ft_getenv(char **env, char *var);
int						find_var_in_env(char **env, char *var);
int						change_env_var(t_global *glo, char *var, int line);
void					change_env_(t_global *glob);

///				SIGNALS					///
void					sigint_handler(int sig_num);
void					sigquit_handler(int sig_num);
void					signal_ctrD(t_global *g);

///				OTHER					///
void					ft_watermark(void);
extern int						g_sig;

///				UTILS					///
size_t					ft_sstrlcpy(char *dst, const char *src, size_t dstsize);
int						is_in_set(char c, char *set);
void					perr(char *str);
void	ft_free_env(t_global *g);
void	ft_free_glob(t_global *glob);

#endif