/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:23:02 by maemaldo          #+#    #+#             */
/*   Updated: 2024/11/21 13:51:49 by maemaldo         ###   ########.fr       */
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

# define PROMPT "\001\033[1;95m\002Poivre-et-shell> \001\033[0m\002"
# define ERR_HD_EOF "warning: here-document delimited by end-of-file\n"
# define ERR_ALLOC "An error has occured, it may\
 be related with a malloc failure\n"

///////////////////////////////////////////
///				STRUCTURES				///
///////////////////////////////////////////

typedef struct s_command
{
	int					infile;
	char				*cmdpath;
	char				**args;
	int					outfile;
	int					pipe[2];
	int					prev_fd;
	int					stdin_copy;
	int					stdout_copy;
	struct s_command	*next;

}						t_command;

typedef struct s_global
{
	t_command			*command;
	t_command			*tmp;
	char				**env;
	int					exit_value;
	char				*line;
	int					last_pid;
}						t_global;

///////////////////////////////////////////
///				PROTOTYPES				///
///////////////////////////////////////////

///				EXECUTION				///

int						ft_exec(t_global *s_global);
void					execve_cmd(t_global *g);
int						check_is_cmd_is_ok(t_global *g, int i);
int						pipe_and_fork(t_global *g, int i);
void					exec_which_cmd(t_global *g);
int						dup_infile_and_outfile(t_global *g);
void					close_fd(t_global *g);
void					close_all_fd_child(t_global *g);
void					error_dup(t_global *g);
void					ft_waitall(t_global *global);

///				TOKENISATION			///

t_command				*ft_token(char *command, t_global *global);
int						ft_check_line(t_global *global);
int						ft_get_arg(t_global *global, char *dest, char *str);
int						ft_size_token(t_global *global, char *str);
int						ft_tokencpy(t_global *global, char *dest, char *src,
							int *pos);
int						ft_get_size_qtoken(t_global *global, char *str,
							int *idx, int *size);
int						ft_envname_len(char *str);
int						ft_env_len_bis(t_global *global, char *str);
char					*ft_env_var(t_global *global, char *str);

///				REDIRECTION				///

int						ft_redir(t_global *global, char *line);
int						ft_heredoc(t_global *global, char *line);
int						ft_infile(t_global *global, char *line);
int						ft_outfile(t_global *global, char *line);
int						ft_outfile2(t_global *global, char *line);
char					*ft_hd_parse(t_global *global, char *line);
char					*ft_getlim(t_global *global, char *line, int *in_quote);
char					*ft_get_file_name(t_global *global, char *line);
int						ft_hd_quote(t_global *global, int fd[2], char *lim);
int						ft_hd_nquote(t_global *global, int fd[2], char *lim);
char					*ft_init_hd_tk(t_global *global, char *line);
char					*ft_fill_hd_tk(t_global *global, char *line,
							char *new_line);

///				BUILT-INS				///

int						ft_cd(t_global *glo);
int						ft_pwd(void);
int						ft_echo(t_command *command);
int						ft_exit(t_global *g, int n);
int						ft_env(t_global *glob);
int						ft_export(t_global *glo);
int						ft_unset(t_global *glob);

///				ENV						///

char					**create_env(char **envp);
char					*ft_getenv(char **env, char *var);
char					*ft_var_name(char *var);
int						find_var_in_env(char **env, char *var);
int						add_env_var(t_global *glo, char *var);
int						change_env_var(t_global *glo, char *var, int line);
void					change_env_(t_global *glob);

///				SIGNALS					///
void					sigint_handler(int sig_num);
void					sigquit_handler(int sig_num);
void					signal_ctrd(t_global *g);

///				OTHER					///
extern int				g_sig;

///				UTILS					///
size_t					ft_sstrlcpy(char *dst, const char *src, size_t dstsize);
int						is_in_set(char c, char *set);
void					perr(char *str);
void					free_tab(char **tab);
void					ft_free_glob(t_global *glob);
int						ft_strcmp(const char *s1, const char *s2);
int						ft_skipquotes(char *str, char quote);
void					ft_printcmd(t_command *cmd);
void					ft_free_cmd(t_command *cmd);
int						ft_error_token(char *str);
char					*ft_getcwd(void);

#endif