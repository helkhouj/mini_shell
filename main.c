#include "shell.h"
#include <readline/history.h>
#include <stdio.h>



// just to test things
int main(void)
{
    char **to = tokenize("<< cat file.txt | grep \"hello world\" > output.txt");
    for (int i = 0; to[i]; i++)
        printf("[%s]\n", to[i]);
    for (int i = 0; to[i]; i++)
        free(to[i]);
    free(to);
    return (0);
}
