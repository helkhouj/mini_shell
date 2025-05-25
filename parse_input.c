#include "shell.h"


t_ast *create_empty_node();
int has_pipe(t_token_stream *stream);
t_token *consume_token(t_token_stream *stream);
int peek_token_type(t_token_stream *stream, int offset, t_token_type type);




t_ast *parse_input(t_token_stream *stream)
{
    if (stream->token_count == 0)
        return (create_empty_node());
    if (has_pipe(stream))
        return (parse_pipeline(stream));
    else
        return (parse_cmd(stream));
}


int has_pipe(t_token_stream *stream)
{
    int i;

    i = 0;
    while (i < stream->token_count)
    {
        if (stream->tokens[i]->type == TOKEN_PIPE)
            return (1);
        i++;
    }
    return (0);
}


t_ast *create_empty_node()
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = NODE_EMPTY;
    return (node);
}





int peek_token_type(t_token_stream *stream, int offset, t_token_type type)
{
    if (stream->current_index + offset >= stream->token_count)
        return (0);
    return (stream->tokens[stream->current_index + offset]->type == type);
}
