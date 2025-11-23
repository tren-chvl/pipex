/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_path.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:00:49 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/19 11:03:08 by marcheva         ###   ########.fr       */
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

int	ft_fauxlen(char **tabenvp)
{
	int	i;

	i = 0;
	while (tabenvp[i] && ft_strncmp(tabenvp[i], "PATH=", 5))
		i++;
	return (i);
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
	i = ft_fauxlen(tabenv);
	if (!tabenv[i])
		return (NULL);
	path = ft_split(tabenv[i] + 5, ':');
	while (path[j])
	{
		full_path = ft_strjoin(path[j], cmd);
		if (!full_path)
			return (null_free(path));
		if (access(full_path, X_OK) == 0)
			return (full_free(path, full_path));
		free(full_path);
		j++;
	}
	ft_free_tab(path);
	return (NULL);
}
