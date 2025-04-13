MAKEFLAGS       = --no-print-directory

NAME            = pipex

SRCS            = srcs/pipex_bonus.c srcs/pipex_utils_bonus.c srcs/pipex_utils.c srcs/pipex.c
OBJS            = ${SRCS:.c=.o}

CC              = cc
CFLAGS          = -Wall -Wextra -Werror -Iincludes

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

all: ${NAME}

${NAME}: ${OBJS}
	@make -C ./libft
	@$(CC) ${CFLAGS} ${OBJS} -Llibft -lft -o ${NAME}
	@echo "Pipex compiled."

clean:
	@make clean -C ./libft
	@rm -f ${OBJS}
	@echo "Cleaned object files."

fclean: clean
	@make fclean -C ./libft
	@rm -f ${NAME}
	@echo "Cleaned all files."

re: fclean all

.PHONY: all clean fclean re
