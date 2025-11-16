#include "pipex.h"

static int  count_word(const char *s, char c)
{
    int count;

    count = 0;
    while (*s)
    {
        while (*s && *s == c)
            s++;
        if (*s)
        {
            count++;
            while (*s && *s != c)
                s++;
        }
    }
    return (count);
}

static char *word_dup(const char *s, char c)
{
    size_t  len;
    size_t  i;
    char    *word;

    len = 0;
    while (s[len] && s[len] != c)
        len++;
    word = malloc(sizeof(char) * (len + 1));
    if (!word)
        return (NULL);
    i = 0;
    while (i < len)
    {
        word[i] = s[i];
        i++;
    }
    word[i] = '\0';
    return (word);
}

void free_tab(char **tab, int n)
{
    int i;

    i = 0;
    while (i < n)
    {
        free(tab[i]);
        i++;
    }
    free(tab);
}

char    **ft_split(const char *s, char c)
{
    int     i;
    int     count;
    char    **tab;

    if (!s)
        return (NULL);
    count = count_word(s, c);
    tab = malloc(sizeof(char *) * (count + 1));
    if (!tab)
        return (NULL);
    i = 0;
    while (*s)
    {
        while (*s && *s == c)
            s++;
        if (*s)
        {
            tab[i] = word_dup(s, c);
            if (!tab[i])
                return (free_tab(tab, i), NULL);
            i++;
            while (*s && *s != c)
                s++;
        }
    }
    tab[i] = NULL;
    return (tab);
}
