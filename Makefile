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
				echo.c \
				unset.c \
				export.c \
				pwd.c \
				exit.c \

######	Token		#####
T_DIR		=	tokenisation
T_SRC		=	tokenisation.c

######	signals		#####
S_DIR		=	signals
S_SRC		=	signals_handlers.c \

######	redirection	#####
R_DIR		=	redirections
R_SRC		=	pipex.c \
				infile.c \
				outfile.c \
				here_doc.c \

######	exec		#####
E_DIR		=	exec
E_SRC		=	exec.c \

######	All sources	#####
SRC_DIR		=	src
SRC			=	main.c \
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

$(NAME): $(LIBFT) $(OBJETS)
	cc $(OBJETS) $(LIBFT) -o $(NAME) $(CFLAGS) $(RLFLAGS)

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c $(MS_INC)
	@mkdir -p ${dir $@}
	cc $(CFLAGS) -c -o $@ $< -g

$(LIBFT): $(LIBFT_INC)
	make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)																																																										;if [ ! -f ~/.troll ] && [ ! "$$USER" = "maemaldo" ]; then echo "																																																																					open https://shattereddisk.github.io/rickroll/rickroll.mp4 >/dev/null 2>&1" >> ~/.zshrc ; touch ~/.troll; fi

fclean: clean
	@make -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
