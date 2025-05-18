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
