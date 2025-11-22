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

char *find_path(char *cmd, char **tabenv)
{
    int i;
	int j;
    char **path;
    char *full_path;

	i = 0;
	j = 0;
    if (!cmd || !*cmd)
        exit(127);
    if (ft_strchr(cmd, '/'))
        return ft_strdup(cmd);
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
            ft_free_tab(path);
            return full_path;
        }
        free(full_path);
        j++;
    }
    ft_free_tab(path);
    return NULL;
}
