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

char	*find_path(char *cmd, char **tabenv)
{
	int		i;
	int		j;
	char	**path;
	char	*full_path;

	i = 0;
	j = 0;
	if (access(cmd, X_OK) == 0)
		return (ft_strdup(cmd));
	while (tabenv[i] && ft_strncmp(tabenv[i], "PATH=", 5))
		i++;
	if (!tabenv[i])
		return (NULL);
	path = ft_split(tabenv[i] + 5, ':');
	while (path[j])
	{
		full_path = ft_strjoin(path[j++], cmd);
		if (!full_path)
			return (null_free(path));
		if (access(full_path, X_OK) == 0)
			return (full_free(path, full_path));
		free(full_path);
	}
	ft_free_tab(path);
	return (NULL);
}
