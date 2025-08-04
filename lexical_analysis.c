#include "shell.h"

t_token *create_token(t_token_type type, char *value)
{
    t_token *new_token;

    new_token = malloc(sizeof(t_token));
    if (!new_token)
        return (NULL);
    new_token->type = type;
    new_token->value = value;
    return (new_token);
}



static t_token_type get_op_type(char *value)
{
    if (!value)
        return (TOKEN_ERROR);
    if (ft_strlen(value) == 1)
        {
            if (value[0] == '|') return (TOKEN_PIPE);
            if (value[0] == '>') return (TOKEN_RED_OUT);
            if (value[0] == '<') return (TOKEN_RED_IN);
        }
    else if (ft_strlen(value) == 2)
        {
            if (value[0] == '>' && value[1] == '>') return (TOKEN_RED_APPEND);
            if (value[0] == '<' && value[1] == '<') return (TOKEN_RED_HEREDOC);
            if (value[0] == '|' && value[1] == '|') return (TOKEN_OR);
            if (value[0] == '&' && value[1] == '&') return (TOKEN_AND);
        }
    return (TOKEN_ERROR);
}

static int add_token(t_token ***tokens_ptr, size_t *count, t_token_type type, char *value)
{
    t_token *new_token;

    new_token = create_token(type, value);
    if (!new_token)
        {
            free(*tokens_ptr);
            *tokens_ptr = NULL;
            return (0);
        }
    if (*count < 1023)
        (*tokens_ptr)[(*count)++] = new_token;
    else
    {
        free_single_token(new_token);
        free(*tokens_ptr);
        *tokens_ptr = NULL;
        return (0);
    }
    return (1); //success
}

static char *process_current_char(char *args, size_t *i, t_token_type *type)
{
    char *token_value;
    char *expanded_value;

    token_value = NULL;
    if (args[*i] == '\'' || args[*i] == '"')
        {
            *type = TOKEN_WORD;
            token_value = extract_quote(args, i);
        }
    else if (is_op(args[*i]))
    {
        token_value = extract_op(args, i);
        *type =get_op_type(token_value);
        if (!token_value || *type == TOKEN_ERROR)
            {
                free(token_value);
                return (NULL);
            }
    }
    else
    {
        *type = TOKEN_WORD;
        token_value = extract_word(args,i);
    }
    
    if (*type == TOKEN_WORD && token_value)
    {
        expanded_value = expand_variables(token_value);
        if (expanded_value)
        {
            free(token_value);
            token_value = expanded_value;
        }
    }
    
    return (token_value);
}

t_token **tokenizer(char *args)
{
    size_t i = 0;
    size_t token_count = 0;
    t_token **tokens;
    char *token_value;
    t_token_type token_type;

    tokens = malloc(sizeof (t_token) * 1024);
    if (!tokens) return (NULL);
    while (args[i])
    {
        while (args[i] && is_space(args[i])) i++;
        if (!args[i]) break ;
        token_value = process_current_char(args, &i, &token_type);
        if (!token_value && token_type != TOKEN_END_OF_INPUT) return (free(tokens), (NULL));
        if (!add_token(&tokens, &token_count, token_type, token_value)) return (NULL);
    }
    if (!add_token(&tokens, &token_count, TOKEN_END_OF_INPUT, NULL)) return (NULL);
    tokens[token_count] = NULL;
    return (tokens);
}



