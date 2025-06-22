SRCS = extra_lib.c frees.c lexical_analysis.c parse_cmd.c parse_input.c parse_pipeline.c parse_redir.c token_stream.c tokenizer_utils.c tester.c
OBJS = ${SRCS:.c=.o}
NAME = minishell
TEST_NAME = test_parser
LIBC = ar rcs
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

.PHONY: all test clean fclean re
