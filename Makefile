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

B_FILES		=	${addprefix src/,${addprefix ${B_DIR}/,${B_SRC}}}

######	Token		#####
T_DIR		=	tokenisation
T_SRC		=	tokenisation.c \
				t_env.c \
				t_utils.c \
				t_checks.c \
				ft_get_arg.c \

T_FILES		=	${addprefix src/,${addprefix ${T_DIR}/,${T_SRC}}}

######	signals		#####
S_DIR		=	signals
S_SRC		=	signals_handlers.c \

S_FILES		=	${addprefix src/,${addprefix ${S_DIR}/,${S_SRC}}}

######	redirection	#####
R_DIR		=	redirections
R_SRC		=	pipex.c \
				redir.c \
				infile.c \
				outfile.c \
				here_doc.c \

R_FILES		=	${addprefix src/,${addprefix ${R_DIR}/,${R_SRC}}}

######	exec		#####
E_DIR		=	exec
E_SRC		=	exec.c \
				exec_one_cmd.c \

E_FILES		=	${addprefix src/,${addprefix ${E_DIR}/,${E_SRC}}}

######	All sources	#####
MAIN_DIR		=	main
MAIN_SRC		=	main.c \
					utils.c \
					ft_watermark.c \

				# ${addprefix ${E_DIR}/,${E_SRC}} \

MAIN_FILES		=	${addprefix src/,${addprefix ${MAIN_DIR}/,${MAIN_SRC}}}

########################
######  OBJECTS  #######
########################

OBJ_DIR		=	objs
MAIN_OBJETS	=	${MAIN_FILES:src/%.c=${OBJ_DIR}/%.o}
T_OBJETS	=	${T_FILES:src/%.c=${OBJ_DIR}/%.o}
B_OBJETS	=	${B_FILES:src/%.c=${OBJ_DIR}/%.o}
S_OBJETS	=	${S_FILES:src/%.c=${OBJ_DIR}/%.o}
R_OBJETS	=	${R_FILES:src/%.c=${OBJ_DIR}/%.o}
E_OBJETS	=	${E_FILES:src/%.c=${OBJ_DIR}/%.o}
ALL_OBJETS	=	${MAIN_OBJETS} \
				${T_OBJETS} \
				${B_OBJETS} \
				${S_OBJETS} \
				${R_OBJETS} \
				${E_OBJETS} \

#########################
######  INCLUDES  #######
#########################

INC_DIR		=	./inc

MS_INC		=	$(INC_DIR)/minishell.h
T_INC		=	$(INC_DIR)/tokenisation.h

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
######  ANSI COLORS  ######
###########################

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
WHITE = \033[0m
BOLD = \033[1m
FLASH = \033[6m
RESET = \033[0m
BANDE = \033[7m #comme moi

###########################
######     RULES     ######
###########################

all : $(NAME)

$(NAME): $(LIBFT) $(T_OBJETS) $(MAIN_OBJETS) $(B_OBJETS) $(S_OBJETS) $(R_OBJETS) $(E_OBJETS)
	@echo -n "${RED}[COMPILING]${WHITE}${NAME}"
	@cc $(ALL_OBJETS) $(LIBFT) -o $(NAME) $(CFLAGS) $(RLFLAGS)
	@echo "\033[2K\r${GREEN}[DONE!]${WHITE}${NAME}"
	@echo "${RED}${BOLD}    ___________  "
	@echo "   ( COMPILED! ) "
	@echo "    ͞ v ͞ ͞ ͞ ͞ ͞ ͞ v ͞  "
	@echo "   /\/\    /\_/\ "
	@echo "  ( ${FLASH}o${RED}${BOLD}w${FLASH}o${RED}${BOLD})  ( ${FLASH}o${RED}${BOLD}.${FLASH}o${RED}${BOLD} )"
	@echo "  / >*<\   > ^ < "
	@echo "   Maël   Anaëlle${WHITE}"

${OBJ_DIR}/${MAIN_DIR}/%.o: src/main/%.c $(MS_INC)
	@mkdir -p ${dir $@}
	@echo -n "\e[2K\r${RED}[COMPILING]${WHITE}$<"
	@cc $(CFLAGS) -c -o $@ $< -g

${OBJ_DIR}/${T_DIR}/%.o: src/${T_DIR}/%.c $(MS_INC) $(T_INC)
	@mkdir -p ${dir $@}
	@echo -n "\e[2K\r${RED}[COMPILING]${WHITE}$<"
	@cc $(CFLAGS) -c -o $@ $< -g

${OBJ_DIR}/${B_DIR}/%.o: src/${B_DIR}/%.c $(MS_INC)
	@mkdir -p ${dir $@}
	@echo -n "\e[2K\r${RED}[COMPILING]${WHITE}$<"
	@cc $(CFLAGS) -c -o $@ $< -g

${OBJ_DIR}/${S_DIR}/%.o: src/${S_DIR}/%.c $(MS_INC)
	@mkdir -p ${dir $@}
	@echo -n "\e[2K\r${RED}[COMPILING]${WHITE}$<"
	@cc $(CFLAGS) -c -o $@ $< -g

${OBJ_DIR}/${R_DIR}/%.o: src/${R_DIR}/%.c $(MS_INC)
	@mkdir -p ${dir $@}
	@echo -n "\e[2K\r${RED}[COMPILING]${WHITE}$<"
	@cc $(CFLAGS) -c -o $@ $< -g

${OBJ_DIR}/${E_DIR}/%.o: src/${E_DIR}/%.c $(MS_INC)
	@mkdir -p ${dir $@}
	@echo -n "\e[2K\r${RED}[COMPILING]${WHITE}$<"
	@cc $(CFLAGS) -c -o $@ $< -g

# @echo "\e[2K\r${GREEN}[OK]${WHITE}$<"

$(LIBFT): $(LIBFT_INC)
	@make -sC $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)
	@echo "$(RED)[DELETED]$(WHITE)$(OBJ_DIR)/"

fclean: clean
	@make -sC $(LIBFT_DIR) fclean
	@rm -rf $(NAME)
	@echo "$(RED)[DELETED]$(WHITE)$(NAME)"

re: fclean all

.PHONY : all clean fclean re
