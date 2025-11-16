#include "pipex.h"

int error_msg(char *msg)
{
    perror(msg);
    return (1);
}

int ft_strlen(char *str)
{
    int i;

    i = 0;
    while (str[i])
    {
        i++;
    }
    return (i);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while ((s1[i] || s2[i]) && i < n)
	{
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	if (i < n)
	{
		return (s1[i] - s2[i]);
	}
	return (0);
}

char *ft_strjoin(char *dir, char *cmd)
{
    char *join;
    int i;
    int j;

    j = 0;
    i =0;
    join = malloc(sizeof(char) * (ft_strlen(dir) + ft_strlen(cmd)+ 2));
    if (!join)
        return (NULL);
    while (dir[i])
    {
        join[i] = dir[i];
        i++;
    }
    join[i++] = '/';
    while (cmd[j])
    {
        join[i] = cmd[j];
        j++;
        i++;
    }
    join[i] = '\0';
    return (join);
}
