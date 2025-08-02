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
    dup = malloc ((len + 1) * sizeof(char));
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


char	*ft_strdup(const char *s)
{
	int		len;
	int		i;
	char	*dup;

	len = ft_strlen(s);
	dup = (char *)malloc((len + 1) * sizeof(char));
	if (dup == NULL)
		return (0);
	i = 0;
	while (s[i])
	{
		dup[i] = s[i];
		i++;
	}
	dup[i] = '\0';
	return (dup);
}


void	*ft_memcpy(void *dest, void *src, size_t n)
{
	unsigned char	*d;
	unsigned char	*s;
	size_t			i;

	if (!dest && !src && n > 0)
		return (NULL);
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
