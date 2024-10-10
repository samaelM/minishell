/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maemaldo <maemaldo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 18:23:02 by maemaldo          #+#    #+#             */
/*   Updated: 2024/10/10 16:24:31 by maemaldo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

///////////////////////////////////////////
///				INCLUDES				///
///////////////////////////////////////////

# include "../lib/libft/libft.h"
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
	t_list				*env_list;
	int					exit_value;
}						t_global;

///////////////////////////////////////////
///				PROTOTYPES				///
///////////////////////////////////////////

///				EXECUTION				///

int						ft_exec_cmd(int fd, char **arg, char **envp,
							char **path);

///				COMPARATOR				///

int						ft_and(void);
int						ft_or(void);

///				PIPES					///

int						ft_pipex(void);

///				TOKENISATION			///

t_command				*ft_token(char *command);
void					ft_free_cmd(t_command *cmd);
void					ft_printcmd(t_command *cmd);
int						ft_check_line(char *str);
int						ft_size_token(char *str);
int						ft_get_arg(char *dest, char *str);
int						ft_redir(t_command *cmd, char *line);
int						ft_envname_len(char *str);
int						ft_env_len_bis(char *str);
char					*ft_env_var(char *str);
int						ft_skipquotes(char *str, char quote);
int						ft_redir_len(char *str);

///				REDIRECTION				///

int						ft_heredoc(t_command *cmd, char *line);
int						ft_infile(t_command *cmd, char *line);
int						ft_outfile(t_command *cmd, char *line);
int						ft_outfile2(t_command *cmd, char *line);

///				BUILT-INS				///

int						ft_cd(void);
int						ft_echo(void);
int						ft_env(void);
int						ft_exit(void);
int						ft_export(void);
int						ft_pwd(void);
int						ft_unset(void);

///				SIGNALS					///
void					sigint_handler(int sig_num);
void					sigquit_handler(int sig_num);

///				OTHER					///
void					ft_watermark(void);

///				UTILS					///
size_t					ft_sstrlcpy(char *dst, const char *src, size_t dstsize);
int						is_in_set(char c, char *set);
void					perr(char *str);

#endif