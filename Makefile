SRCS = main.c extra_lib.c tokenizer.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
LIBC = ar rcs
CC = cc
RM = rm -rf
#FLAGS = -Wall -Wextra -Werror uncomment this and add it in %.o = %.c

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) ${OBJS} -o ${NAME}

%.o: %.c
	$(CC) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
