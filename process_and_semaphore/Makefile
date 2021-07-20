#==============================================================================#
#=================================>MAKEFILE<===================================#
#==============================================================================#

#==================================>COLORS<====================================#

_RED		=	\e[31m
_YELLOW		=	\e[33m
_GREEN		=	\e[32m
_END		=	\e[0m

#==================================>FILES<=====================================#

SRCS			=	main.c \
				srcs/create_struct.c \
				srcs/start_philosophers.c \
				srcs/philo_actions.c \
				srcs/utils.c

#===============================>COMPILATIONS<=================================#

GCC			=	gcc

CFLAGS		=	-Wall -Werror -Wextra

#===================================>DELETE<===================================#

RM			=	rm -rf

#=================================>DIRECTORIES<================================#

DIR_HEAD	=	./include

#===============================>COMPILED_SOURCES<=============================#

OBJS		=	${SRCS:%.c=%.o}

NAME		=	philo

#================================>COMPILED_RULES<==============================#

all:			${NAME}

${NAME}:		${OBJS}
				@${GCC} ${CFLAG} -o ${NAME} ${OBJS}
				@printf "\033[2K\r${_GREEN} FILE create: '${NAME}'. ${_END}✅\n"

#===========================>COMPILED_SOURCES_RULES<===========================#

%.o:			%.c
				@$(GCC) $(CFLAGS) -I $(DIR_HEAD) -c $< -o $@
				@printf "\033[2K\r$(_YELLOW) Compiling $< $(_END)⌛"

#===================================>NORM_RULES<===============================#

norm:
				@norminette .			

#====================================>CLEAN_RULES<=============================#

clean:
			@rm -f ${OBJS}
			@printf "\033[2K\r${_RED} '".o"' has been deleted. ${_END}🗑️\n"

fclean:		clean
			@rm -f ${NAME}
			@printf "\033[2K\r${_RED} '"${NAME}"' has been deleted. ${_END}🗑️\n"

re:			fclean all

.PHONY: all clean fclean re