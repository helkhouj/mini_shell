#include "shell.h"

size_t ft_strlen(const char *s)
{
    size_t len;

    len = 0;
    while (*s)
    {
        len++;
        s++;
    }
    return (len);
}

char *ft_strndup(const char *s, size_t n)
{
    size_t len;
    size_t i;
    char *dup;

    len = ft_strlen(s);
    if (len > n)
        len = n;
    dup = malloc (len * sizeof(char) + 1);
    if (!dup)
        return (0);
    i = 0;
    while (i < len && s[i])
    {
        dup[i] = s[i];
        i++;
    }
    dup[i] = '\0';
    return (dup);
}
