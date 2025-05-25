#include "shell.h"

t_token_stream *init_token_stream(t_token **token_array, int count)
{
    t_token_stream *stream;

    stream = malloc(sizeof(t_token_stream));
    if (!stream)
        {
            printf("Error allocation memory for token stream.\n");
            return (NULL);
        }
    stream->tokens = token_array;
    stream->current_index = 0;
    stream->token_count = count;

    return (stream);
}


t_token *consume_token(t_token_stream *stream)
{
    t_token *current;

    if (stream->current_index >= stream->token_count)
        return (NULL);
    current = stream->tokens[stream->current_index];
    stream->current_index++;
    return (current);
}

void free_token_stream(t_token_stream *stream)
{
    if (!stream)
        return;
    stream->current_index = 0;
    stream->token_count = 0;
    free(stream);
}


t_token *get_current_token(t_token_stream *stream)
{
    if (stream->current_index >= stream->token_count)
        return (NULL);
    return (stream->tokens[stream->current_index]);
}

