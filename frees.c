#include "shell.h"


void free_ast_node(t_ast *node)
{
    if (!node)
        return;

    if (node->type == NODE_COMMAND)
    {
        free_cmd_args(node->command_args);
        free_redir_list(node->next);
    }
    else if (node->type == NODE_PIPE)
    {
        free_ast_node(node->left);
        free_ast_node(node->right);
    }
    free(node);
}



void free_cmd_args(char **args)
{
    int i;

    if (!args)
        return ;
    i = 0;
    while (args[i])
    {
        free(args[i]);
        i++;
    }
    free(args);

}

void free_token_array(t_token **tokens, int count)
{
    if (!tokens)
        return ;
    for (int i = 0; i < count; i++)
        free_single_token(tokens[i]);
   free(tokens);
}


void free_single_token(t_token *token)
{
    if (!token)
        return ;
    free(token->value);
    free(token);
}