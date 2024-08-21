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
				echo.c \
				env.c \
				exit.c \
				export.c \
				pwd.c \
				unset.c \

######	Token		#####
T_DIR		=	tokenisation
T_SRC		=	tokenisation.c

######	Token		#####
S_DIR		=	signals
S_SRC		=	signals_handlers.c \

######	All sources	#####
SRC_DIR		=	src
SRC			=	main.c \
				ft_watermark.c \
				${addprefix ${B_DIR}/,${B_SRC}} \
				${addprefix ${T_DIR}/,${T_SRC}} \
				${addprefix ${S_DIR}/,${S_SRC}} \

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

LIB_DIR		=	./lib

LIBFT_DIR	=	$(LIB_DIR)/libft

LIBFT		=	libft.a

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

$(NAME): $(LIBFT_DIR)/$(LIBFT) $(OBJETS)
	cc $(OBJETS) $(LIBFT_DIR)/$(LIBFT) -o $(NAME) $(CFLAGS) $(RLFLAGS)

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c $(INC_DIR)/minishell.h
	@mkdir -p ${dir $@}
	cc $(CFLAGS) -c -o $@ $< -g

$(LIBFT_DIR)/$(LIBFT): $(LIBFT_DIR)/libft.h
	make -C $(LIBFT_DIR)

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make -C lib/libft/ fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY : all clean fclean re
