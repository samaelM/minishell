########################
######   NAME    #######
########################

NAME 		= minishell

########################
######  SOURCES  #######
########################

######	Builtins	#####
B_DIR		=	builtins
B_SRC		=	cd.c \
				env.c \
				env_utils.c \
				echo.c \
				unset.c \
				export.c \
				pwd.c \
				exit.c \

######	Token		#####
T_DIR		=	tokenisation
T_SRC		=	tokenisation.c \
				t_env.c \
				t_utils.c \
				t_checks.c \
				ft_get_arg.c \

######	signals		#####
S_DIR		=	signals
S_SRC		=	signals_handlers.c \

######	redirection	#####
R_DIR		=	redirections
R_SRC		=	pipex.c \
				redir.c \
				infile.c \
				outfile.c \
				here_doc.c \

######	exec		#####
E_DIR		=	exec
E_SRC		=	exec.c \
				exec_one_cmd.c \

######	All sources	#####
SRC_DIR		=	src
SRC			=	main.c \
				utils.c \
				ft_watermark.c \
				${addprefix ${B_DIR}/,${B_SRC}} \
				${addprefix ${T_DIR}/,${T_SRC}} \
				${addprefix ${S_DIR}/,${S_SRC}} \
				${addprefix ${R_DIR}/,${R_SRC}} \
				${addprefix ${E_DIR}/,${E_SRC}} \

FILES		=	${addprefix ${SRC_DIR}/,${SRC}}

########################
######  OBJECTS  #######
########################

OBJ_DIR		=	objs
OBJETS		=	${FILES:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}

#########################
######  INCLUDES  #######
#########################

INC_DIR		=	./inc

MS_INC		=	$(INC_DIR)/minishell.h

LIB_DIR		=	./lib
LIBFT_DIR	=	$(LIB_DIR)/libft
LIBFT_INC	=	$(LIBFT_DIR)/libft.h
LIBFT		=	$(LIBFT_DIR)/libft.a

###########################
######  COMPILATION  ######
###########################

#####	Mandatory	#####
#####	Flags		#####
CFLAGS		=	-Wall -Wextra -Werror

#####	Read lines	#####
####	Flags		#####
RLFLAGS		=	-lreadline

###########################
######     RULES     ######
###########################

all : $(NAME)

RED = \033[0;31m
GREEN = \e[0;32m
YELLOW = \033[0;33m
WHITE = \033[0m
BOLD = \033[1m
FLASH = \033[6m
BANDE = \033[7m

$(NAME): $(LIBFT) $(OBJETS)
	@echo -n "${RED}[COMPILING]${WHITE}${NAME}"
	@cc $(OBJETS) $(LIBFT) -o $(NAME) $(CFLAGS) $(RLFLAGS)
	@echo "\e[2K\r${GREEN}[OK]${WHITE}${NAME}"
	@echo "${RED}${BOLD}     COMPILED!"
	@echo "   /\/\    /\_/\   "
	@echo "  ( owo)  ( o.o )  "
	@echo "  / >*<\   > ^ <   "
	@echo "   Maël   Anaëlle${WHITE}"

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c $(MS_INC)
	@mkdir -p ${dir $@}
	@echo -n "${RED}[COMPILING]${WHITE}$<"
	@cc $(CFLAGS) -c -o $@ $< -g
	@echo "\e[2K\r${GREEN}[OK]${WHITE}$<"

$(LIBFT): $(LIBFT_INC)
	@make -sC $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -sC $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re


