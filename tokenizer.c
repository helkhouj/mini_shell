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
    else if (str[*i] == '<' && str[*i + 1] == '>')
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

char **tokenize(char *args)
{
    size_t i = 0;
    size_t token_count = 0;
    char **tokens;

    tokens = malloc (1024 * sizeof(char *));
    if (!tokens)
        return (NULL);
    while (args[i])
    {
        while (args[i] && is_space(args[i]))
            i++;
        if (!args[i])
            break ;
        if (args[i] == '\'' || args[i] == '"')
            tokens[token_count++] = extract_quote(args, &i);
        else if (is_op(args[i]))
            tokens[token_count++] = extract_op(args, &i);
        else
        tokens[token_count++] = extract_word(args, &i);
    }
    tokens[token_count] = NULL;
    return (tokens);
}
