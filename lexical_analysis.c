#include "shell.h"

static int is_space(char c)
{
    return ((c >= 9 && c <= 13) || c == 32);
}

static int is_op(char c)
{
    return (c == '|' || c == '<' || c == '>');
}

static char *extract_op(char *str, size_t *i) //extracts an op token ( |, >, <, >>, <<)
{
    size_t start = *i;
    if (str[*i] == '>' && str[*i + 1] == '>')
        *i += 2;
    else if (str[*i] == '<' && str[*i + 1] == '<')
        *i += 2;
    else
        (*i)++;
    return (ft_strndup(str + start , *i - start));
}

static char *extract_quote(char *str, size_t *i) //extracts single/double quotes ', "
{
    size_t start = *i;
    char quote = str[(*i)++];
    while(str[*i] && str[*i] != quote)
        (*i)++;
    if (str[*i] == quote)
        (*i)++;
    return (ft_strndup(str + start, *i - start));
}

static char *extract_word(char *str, size_t *i) //extracts the word
{
    size_t start = *i;

    while (str[*i] && !is_space(str[*i]) && !is_op(str[*i]))
    {
        if (str[*i] == '\'' || str[*i] == '"')
            {
                free(extract_quote(str, i)); // reason i free while i call the function is to increment i
                if (!str[*i])
                    break ;
            }
        else
            (*i)++;
    }
    return (ft_strndup(str + start, *i - start));
}

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

void free_single_token(t_token *token)
{
    if (!token)
        return ;
    free(token->value);
    free(token);
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
    printf("Tokenization is COMPLETE. Generated %zu tokens.\n", token_count);
    return (tokens);
}


void free_token_array(t_token **tokens, int count)
{
    if (!tokens)
        return ;
    for (int i = 0; i < count; i++)
        free_single_token(tokens[i]);
   free(tokens);
}
