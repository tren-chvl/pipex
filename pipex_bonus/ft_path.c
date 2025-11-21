/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:00:49 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:59 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	ft_free_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
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
char *ft_strdup(char *s1)
{
	size_t len;
	char *dest;
	size_t i;

	len = ft_strlen(s1);
	dest = (char *)malloc(sizeof(char) * (len + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int ft_verif(const char *path)
{
	if (access(path, F_OK) != 0)
	{
		if (errno == ENOENT)
			return 1;
		return 1;
	}
	if (access(path, X_OK) != 0)
	{
		if (errno == EACCES)
			return 126;
		return 1;
	}
	return 0;
}

char *find_path(char *cmd, char **tabenv)
{
	int   i = 0, j;
	char **path;
	char *full_path;

	if (ft_strchr(cmd, '/'))
	{
		int code = ft_verif(cmd);
		if (code == 0)
			return ft_strdup(cmd);
		exit(code);
	}
	while (tabenv[i] && ft_strncmp(tabenv[i], "PATH=", 5))
		i++;
	if (!tabenv[i])
		return NULL;
	path = ft_split(tabenv[i] + 5, ':');
	j = 0;
	while (path[j])
	{
		full_path = ft_strjoin(path[j], cmd);
		if (access(full_path, F_OK) == 0)
		{
			int code = ft_verif(full_path);
			if (code == 0)
			{
				ft_free_tab(path);
				return full_path;
			}
			ft_free_tab(path);
			free(full_path);
			exit(code);
		}
		free(full_path);
		j++;
	}
	ft_free_tab(path);
	return NULL;
}


