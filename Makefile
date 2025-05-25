SRCS = extra_lib.c lexical_analysis.c token_stream.c parse_cmd.c parse_input.c frees.c parse_redir.c parse_pipeline.c main.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
LIBC = ar rcs # This line is not used in your current setup, but harmless.
CC = cc
RM = rm -rf
CFLAGS = -Wall -Wextra -Werror
LDFLAGS = -lreadline -lhistory

all: ${NAME}

${NAME}: ${OBJS}
	$(CC) $(CFLAGS) ${OBJS} $(LDFLAGS) -o ${NAME}

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re
