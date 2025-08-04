#include "shell.h"

static int g_last_exit_status = 0;

void set_exit_status(int status) //usefull in the execution part
{
    g_last_exit_status = status;
}

static char *int_to_str(int n) //cuz $? take a string representation not the int itself(for the set_exit_status)
{
    int (i), (temp), (digits);
    char *result = malloc(12);
    if (!result)
        return (NULL);
    i = 0;
    if (n == 0)
    {
        result[i++] = '0';
        result[i] = '\0';
        return (result);
    }
    if (n < 0)
    {
        result[i++] = '-';
        n = -n;
    }
    temp = n;
    digits = 0;
    while (temp > 0)
    {
        temp /= 10;
        digits++;
    }
    i += digits;
    result[i] = '\0';
    while (n > 0)
    {
        result[--i] = (n % 10) + '0';
        n /= 10;
    }
    return (result);
}

static char *get_var_value(char *var_name) //take a var name and returns its string name, uses getenv(VAR)
{
    char *env_val;
    
    if (!var_name)
        return (ft_strdup(""));
    if (var_name[0] == '?' && var_name[1] == '\0')
        return (int_to_str(g_last_exit_status));
    env_val = getenv(var_name);
    if (env_val)
        return (ft_strdup(env_val));
    return (ft_strdup(""));
}

static char *extract_var_name(char *str, size_t *i)//extracts the var name after $
{
    size_t start;
    
    start = *i;
    
    if (str[*i] == '?')
    {
        (*i)++;
        return (ft_strndup(str + start, 1));
    }
    while (str[*i] && (str[*i] == '_' || (str[*i] >= 'A' && str[*i] <= 'Z') || 
                       (str[*i] >= 'a' && str[*i] <= 'z') || (str[*i] >= '0' && str[*i] <= '9')))
        (*i)++;
    return (ft_strndup(str + start, *i - start));
}

char *expand_variables(char *str)
{
   size_t (len), (i), (j), (var_len);
   int (in_single_quote), (in_double_quote);
   char (*result), (*var_name), (*var_value);
   if (!str)
      return (NULL);
    
   len = ft_strlen(str);
   result = malloc(len * 4 + 1);// why the *4 + 1 ?
   if (!result)
      return (NULL);
   i = 0, j = 0;
   in_single_quote = 0;
   in_double_quote = 0;
    while (str[i])
    {
        if (str[i] == '\'' && !in_double_quote)
        {
            in_single_quote = !in_single_quote;
            result[j++] = str[i++];
        }
        else if (str[i] == '"' && !in_single_quote)
        {
            in_double_quote = !in_double_quote;
            result[j++] = str[i++];
        }
        else if (str[i] == '$' && !in_single_quote && str[i + 1])
        {
            i++;
            var_name = extract_var_name(str, &i);
            var_value = get_var_value(var_name);
            var_len = ft_strlen(var_value);
            // TODO: Add realloc here if buffer size exceeded (len * 4)
            ft_memcpy(result + j, var_value, var_len);
            j += var_len;
            free(var_name);
            free(var_value);
        }
        else
            result[j++] = str[i++];
    }
    
    result[j] = '\0';
    return (result);
}