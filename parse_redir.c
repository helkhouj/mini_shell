#include "shell.h"


void free_redir_list(t_ast *head);
t_ast *create_redir_node(t_token_type type, char *filename);

int parse_redirection(t_token_stream *stream, t_ast **redir_list_head)
{
    t_ast *redir_head;
    t_ast *redir_current;
    t_token *op_token;
    t_token *filename_token;
    char *filename;
    t_ast *redir_node;

    redir_head = NULL;
    redir_current = NULL;
    *redir_list_head = NULL; 

    while (peek_token_type(stream, 0, TOKEN_RED_IN) || peek_token_type(stream, 0, TOKEN_RED_OUT) || peek_token_type(stream, 0, TOKEN_RED_APPEND) || peek_token_type(stream, 0, TOKEN_RED_HEREDOC))
    {
        op_token = consume_token(stream);
        if (!op_token)
        {
            free_redir_list(redir_head);
            return (-1);
        }

        filename_token = consume_token(stream);
        if (!filename_token || filename_token->type != TOKEN_WORD)
        {
            free_redir_list(redir_head);
            return (-1);
        }

        filename = ft_strdup(filename_token->value);
        if (!filename)
        {
            free_redir_list(redir_head);
            return (-1);
        }

        redir_node = create_redir_node(op_token->type, filename);
        if (!redir_node)
        {
            free(filename);
            free_redir_list(redir_head);
            return (-1);
        }
        if (redir_head == NULL)
        {
            redir_head = redir_node;
            redir_current = redir_node;
        }
        else
        {
            redir_current->next = redir_node;
            redir_current = redir_node;
        }
    }
    *redir_list_head = redir_head;
    return (0);
}





t_ast *create_redir_node(t_token_type type, char *filename)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    if (type == TOKEN_RED_IN)
        node->type = NODE_RED_IN;
    else if (type == TOKEN_RED_OUT)
        node->type = NODE_RED_OUT;
    else if (type == TOKEN_RED_APPEND)
        node->type = NODE_RED_APPEND;
    else if (type == TOKEN_RED_HEREDOC)
        node->type = NODE_RED_HEREDOC;
    else
    {
        free(node);
        return (NULL);
    }
    node->red_file = filename;
    node->next = NULL;
    node->command_args = NULL;
    node->left = NULL;
    node->right = NULL;
    node->red_fd = 0;
    return (node);
}


void free_redir_list(t_ast *head)
{
    t_ast *tmp;

    while (head)
    {
        tmp = head;
        head = head->next;
        free(tmp->red_file);
        free(tmp);
    }
}
