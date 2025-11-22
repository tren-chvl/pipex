#include "pipex.h"

char	*ft_strjoin(char *dir, char *cmd)
{
	char	*join;
	int		i;
	int		j;

	j = 0;
	i = 0;
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

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] == s2[i])
	{
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

void ft_bzero(void *s, size_t n)
{
	size_t i;
	unsigned char *str;

	str = (unsigned char *)s;
	i = 0;
	while ( i < n)
	{
		str[i] = 0;
		i++;
	}
}

char	*null_free(char **tab)
{
	ft_free_tab(tab);
	return (NULL);
}

char	*full_free(char **tab, char *full)
{
	ft_free_tab(tab);
	return (full);
}
