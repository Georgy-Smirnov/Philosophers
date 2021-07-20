#==============================================================================#
#=================================>MAKEFILE<===================================#
#==============================================================================#

#==================================>COLORS<====================================#

#==================================>COLORS<====================================#

_BLUE		=	\e[34m
_RED		=	\e[31m
_END		=	\e[0m

#===================================>DELETE<===================================#

RM			=	rm -rf

#=================================>DIRECTORIES<================================#

DIR_1	=	./threads_and_mutex

DIR_2	=	./process_and_semaphore

#===================================>FILES<====================================#

FILE1	=	philo_threads_and_mutex

FILE2	=	philo_process_and_semaphore

#================================>COMPILED_RULES<==============================#

all:		${FILE1} ${FILE2}

${FILE1}:
			@printf "\033[2K\r${_BLUE}  PHILO threads_and_mutex:${_END}\n"
			@${MAKE} -C ${DIR_1}
			@cp -rf ${DIR_1}/philo ./${FILE1}

${FILE2}:
			@printf "\033[2K\r${_BLUE}  PHILO process_and_semaphore:${_END}\n"
			@${MAKE} -C ${DIR_2}
			@cp -rf ${DIR_2}/philo ./${FILE2}

#===================================>NORM_RULES<===============================#

norm:
				@norminette .			

#====================================>CLEAN_RULES<=============================#

clean:
			@make clean -C ${DIR_1}
			@make clean -C ${DIR_2}

fclean:
			@make fclean -C ${DIR_1}
			@make fclean -C ${DIR_2}
			@rm -f ${FILE1}
			@rm -f ${FILE2}
			@printf "\033[2K\r${_RED} FILES has been deleted. ${_END}🗑️\n"

re:			fclean all

.PHONY: all clean fclean re