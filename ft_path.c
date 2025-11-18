/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:00:49 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/18 14:39:41 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    ft_free_tab(char **tab)
{
	int i;

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

char *null_free(char **tab)
{
	ft_free_tab(tab);
	return (NULL);
}

char *full_free(char **tab,char *full)
{
	ft_free_tab(tab);
	return (full);
}
char *find_path(char *cmd, char **tabenv)
{
	int i;
	int j;
	char **path;
	char *full_path;
	char *tmp;

	i = 0;
	j = 0;
	while (tabenv[i] && ft_strncmp(tabenv[i], "PATH=", 5))
		i++;
	if (!tabenv[i])
		return  (NULL);
	path = ft_split(tabenv[i] + 5, ':');
	while (path[j])
	{
		tmp = ft_strjoin(path[j], "/");
		full_path = ft_strjoin(tmp,cmd);
		free(tmp);
		if (!full_path)
			return (null_free(path));
		if (access(full_path,X_OK) == 0)
			return (full_free(path,full_path));
		free(full_path);
		j++;
	}
	ft_free_tab(path);
	return (NULL);
}
