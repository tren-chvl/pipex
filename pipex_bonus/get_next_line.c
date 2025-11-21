/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:26:35 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 13:47:57 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*clean_line(char *line)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	if (!line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (!line[i])
		return (free_return(line, NULL));
	i++;
	str = malloc(sizeof(char) * (ft_strlen_g(line + i) + 1));
	if (!str)
		return (free(line), NULL);
	while (line[i])
		str[j++] = line[i++];
	str[j] = '\0';
	free(line);
	if (str[0] == '\0')
		return (free_return(str, NULL));
	return (str);
}

char	*extract_line(char *line)
{
	char	*extract;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!line || !*line)
		return (NULL);
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\n')
		i++;
	extract = malloc(sizeof(char) * (i + 1));
	if (!extract)
		return (NULL);
	while (j < i)
	{
		extract[j] = line[j];
		j++;
	}
	extract[j] = '\0';
	return (extract);
}

char	*read_newline(int fd, char *line)
{
	char	*buffer;
	ssize_t	read_byte;

	buffer = malloc((BUFFER_SIZE + 1));
	read_byte = 1;
	if (!buffer)
		free_return(line, NULL);
	while (read_byte > 0 && !ft_strchr(line, '\n'))
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)
		{
			free(buffer);
			free(line);
			return (NULL);
		}
		buffer[read_byte] = '\0';
		line = ft_strjoin_gnl(line, buffer);
		if (!line)
			free_return(line, NULL);
	}
	free(buffer);
	return (line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*str;
	char		*tmp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = read_newline(fd, line);
	if (!line)
	{
		if (line)
		{
			free(line);
			line = NULL;
		}
		return (NULL);
	}
	str = extract_line(line);
	tmp = clean_line(line);
	line = tmp;
	return (str);
}
