#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <readline/readline.h>
#include <readline/history.h>


size_t ft_strlen(const char *s);
char *ft_strndup(const char *s, size_t n);
char **tokenize(char *args);

#endif
