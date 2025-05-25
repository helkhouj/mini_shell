#include "shell.h"

t_ast *create_pipe_node(t_ast *left, t_ast *right);


t_ast *parse_pipeline(t_token_stream *stream)
{
    t_ast *left_cmd;
    t_ast *right_cmd;
    t_token *pipe_token;

    left_cmd = parse_cmd(stream);
    if (!left_cmd)
        return (NULL);
    while (peek_token_type(stream, 0, TOKEN_PIPE))
    {
        pipe_token = consume_token(stream);
        if (!pipe_token)
            {
                free_ast_node(left_cmd);
                return (NULL);
            }
        right_cmd = parse_cmd(stream);
        if (!right_cmd)
            {
                free_ast_node(left_cmd);
                return (NULL);
            }
        left_cmd = create_pipe_node(left_cmd, right_cmd);
        if (!left_cmd)
            return (NULL);
    }
    return (left_cmd);
}


t_ast *create_pipe_node(t_ast *left, t_ast *right)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
            return (NULL);
    node->type = NODE_PIPE;
    node->command_args = NULL;
    node->red_fd = 0;
    node->red_file = NULL;
    node->next = NULL;
    node->left = left;
    node->right = right;
    return (node);
}
