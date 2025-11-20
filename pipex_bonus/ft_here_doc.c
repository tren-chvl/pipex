/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:37:34 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 16:46:25 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    read_here_doc(char *limiter, int fd)
{
    char    *line;

    while ((line = get_next_line(STDIN_FILENO)))
    {
        if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
            && (line[ft_strlen(limiter)] == '\n'
            || line[ft_strlen(limiter)] == '\0'))
        {
            free(line);
            break ;
        }
        write(fd, line, ft_strlen(line));
        free(line);
    }
    close(fd);
}



int	init_here_doc(char *limiter)
{
	int	fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (fork() == 0)
	{
		close(fd[0]);
		read_here_doc(limiter, fd[1]);
		exit(0);
	}
	close(fd[1]);
	return (fd[0]);
}

void	wait_all(void)
{
	while (wait(NULL) > 0)
		;
}

void	run_commands(t_data *data, int prev_fd)
{
	int	fd[2];
	int	i;

	i = 3;
	while (i < data->argc - 2)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		exec_middle(prev_fd, data->argv[i], data->envp, fd);
		prev_fd = fd[0];
		i++;
	}
	exec_last(prev_fd, data->outfile, data->argv[data->argc - 2], data->envp);
}

int	here_doc(int argc, char **argv, char **envp)
{
	t_data	data;
	int		prev_fd;

	if (argc < 6)
		return (error_msg("error argument :( "));
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (data.outfile < 0)
		return (perror("outfile"), 1);
	prev_fd = init_here_doc(argv[2]);
	if (prev_fd < 0)
		return (1);
	run_commands(&data, prev_fd);
	wait_all();
	return (0);
}
