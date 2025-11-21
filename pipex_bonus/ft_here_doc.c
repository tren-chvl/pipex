/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_here_doc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 18:30:00 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 18:30:00 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void read_here_doc(char *limiter, int fd[2])
{
	char *line;

	close(fd[0]);
	while (1)
	{
		write(1, "heredoc> ", 9);
		line = get_next_line(STDIN_FILENO);
		if (!line)
			break;
		if (ft_strncmp(line, limiter, ft_strlen(limiter)) == 0
			&& line[ft_strlen(limiter)] != '\0'
			&& line[ft_strlen(limiter)] == '\n')
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
		free(line);
	}
	close(fd[1]);
	exit(0);
}


int init_here_doc(char *limiter)
{
	int fd[2];

	if (pipe(fd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	if (fork() == 0)
		read_here_doc(limiter, fd);
	close(fd[1]);
	return (fd[0]);
}

void wait_all(pid_t last_pid)
{
	int status;
	pid_t pid;
	int exit_code = 0;

	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
	}
	exit(exit_code); 
}
pid_t run_commands(t_data *data, int prev_fd)
{
    int fd[2];
    int i;
    pid_t last_pid;

    i = 3;
    while (i < data->argc - 2)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe");
            exit(1);
        }
        exec_middle(prev_fd, data->argv[i], data->envp, fd);
        close(prev_fd);
        close(fd[1]);
        prev_fd = fd[0];
        i++;
    }
    last_pid = exec_last(prev_fd, data->argv[data->argc - 2], data->envp, data);
    close(prev_fd);
    return (last_pid);
}
void close_all_fds(void)
{
    int fd;
    for (fd = 3; fd < 1024; fd++)
        close(fd);
}



int here_doc(int argc, char **argv, char **envp)
{
	t_data data;
	int prev_fd;
	pid_t last_pid;

	if (argc < 6)
		return (error_msg("error argument :( "));
	ft_bzero(&data, sizeof(t_data));
	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.outfile_path = argv[argc - 1];
	data.append = 1;
	prev_fd = init_here_doc(argv[2]);
	if (prev_fd < 0)
		return (1);
	last_pid = run_commands(&data, prev_fd);
	close_all_fds();
	wait_all(last_pid);
	return (0);
}
