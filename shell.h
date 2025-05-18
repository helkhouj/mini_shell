#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum e_node_type
{
    NODE_COMMAND,
    NODE_PIPE,
    NODE_RED_IN,
    NODE_RED_OUT,
    NODE_RED_APPEND,
    NODE_RED_HEREDOC,
    NODE_AND,
    NODE_OR
} t_node_type;

typedef enum e_token_type
{
    TOKEN_ERROR,
    TOKEN_WORD,
    TOKEN_PIPE,
    TOKEN_RED_IN,
    TOKEN_RED_OUT,
    TOKEN_RED_APPEND,
    TOKEN_RED_HEREDOC,
    TOKEN_END_OF_INPUT
} t_token_type;

typedef struct s_token
{
    t_token_type type;
    char *value;
} t_token;


typedef struct s_token_stream
{
    t_token **tokens;
    int current_index;
    int token_count;
}   t_token_stream;

typedef struct s_ast
{
    t_node_type type;
    char **command_args;
    struct s_ast *left;  //pointer to the AST node on the left side of the op
    struct s_ast *right; //pointer to the AST node on the right side of the op

    int red_fd;  //fd being red ( stdin, stdout)
    char *red_file; //path to the file of red
    //for the << i need to understand the heredoc, i didnt do this part in pipex
} t_ast;



size_t ft_strlen(const char *s);
char *ft_strndup(const char *s, size_t n);
t_token **tokenizer(char *args);
void free_token_array(t_token **tokens, int count);






//TO_DO
t_token_stream *init_token_stream(t_token **token_array, int count);
void free_token_stream(t_token_stream *stream);
t_token *get_current_token(t_token_stream *stream);
t_token *peek_token(t_token_stream *stream, int offset);
void consume_token(t_token_stream *stream);


#endif
