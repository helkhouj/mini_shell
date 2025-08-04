#include "shell.h"

t_ast *create_cmd_node(char **command_args, t_ast *redir);
int parse_args(t_token_stream *stream, char ***args);
char **assemble_cmd_args(char *cmd_name, char **args_list);


t_ast *parse_cmd(t_token_stream *stream)
{
    t_token *cmd_token;
    char *cmd_name;
    char **args_from_parse_args = NULL; // Arguments *after* the command name
    char **final_command_args = NULL; // The complete array for t_ast->command_args
    int args_rc;
    t_ast *cmd_node;
    t_ast *redirs;
    int redir_rc;

    cmd_token = consume_token(stream);
    if (!cmd_token || cmd_token->type != TOKEN_WORD)
        return (NULL);
    cmd_name = ft_strdup(cmd_token->value);
    if (!cmd_name)
        return (NULL);
    args_rc = parse_args(stream, &args_from_parse_args);
    if (args_rc == -1)
    {
        free(cmd_name);
        return (NULL);
    }
    redirs = NULL;
    redir_rc = parse_redirection(stream, &redirs);
    if (redir_rc == -1)
    {
        free(cmd_name);
        free_cmd_args(args_from_parse_args);
        return (NULL);
    }

    // Assemble the full command arguments array
    final_command_args = assemble_cmd_args(cmd_name, args_from_parse_args);
    if (!final_command_args)
    {
        // assemble_command_args handles freeing cmd_name and args_from_parse_args if it fails.
        // So we only need to free redirs here.
        free_redir_list(redirs);
        return (NULL);
    }

    cmd_node = create_cmd_node(final_command_args, redirs);
    if (!cmd_node)
    {
        free_cmd_args(final_command_args); // Free the combined array as create_cmd_node failed
        free_redir_list(redirs);
        return (NULL);
    }
    return (cmd_node);
}





int parse_args(t_token_stream *stream, char ***args)
{
    int count;
    int capacity;
    t_token *token;
    char **tmp;

    count = 0;
    capacity = 16;
    *args = malloc(capacity * sizeof(char *));
    if (!*args)
        return (-1);
    while (peek_token_type(stream, 0, TOKEN_WORD))
    {
        if (count >= capacity)
        {
            capacity *= 2;
            tmp = malloc(capacity * sizeof(char *));
            if (!tmp)
            {
                free_cmd_args(*args);
                *args = NULL;
                return (-1);
            }
            ft_memcpy(tmp, *args, count * sizeof(char *));
            free(*args);
            *args = tmp;
        }
        token = consume_token(stream);
        if (!token)
        {
            free_cmd_args(*args);
            *args = NULL;
            return (-1);
        }
        (*args)[count++] = ft_strdup(token->value);
        if (!(*args)[count - 1])
        {
            free_cmd_args(*args);
            *args = NULL;
            return (-1);
        }
    }
    (*args)[count] = NULL;
    return (0);
}


t_ast *create_cmd_node(char **command_args, t_ast *redir)
{
    t_ast *node;

    node = malloc(sizeof(t_ast));
    if (!node)
        return (NULL);
    node->type = NODE_COMMAND;
    node->command_args = command_args;
    node->left = NULL;
    node->right = NULL;
    node->next = redir;
    node->red_fd = 0;
    node->red_file = NULL;
    return (node);
}




char **assemble_cmd_args(char *cmd_name, char **args_list)
{
    int total_len = 1;
    int i = 0;
    char **new_args_arr;
    if (args_list)
        {
            while (args_list[i])
            {
                total_len++;
                i++;
            }
        }
    new_args_arr = malloc(sizeof(char *) * (total_len + 1));
    if(!new_args_arr)
        {
            if (! cmd_name)
                free(cmd_name);
            if (!args_list)
                free_cmd_args(args_list);
            return (NULL);
        }
    new_args_arr[0] = cmd_name;
    i = 0;
    while (i < total_len)
    {
        new_args_arr[i + 1] =args_list[i];
        i++;
    }
    new_args_arr[total_len] = NULL;
    if (args_list)
        free(args_list);
    return (new_args_arr);
}
