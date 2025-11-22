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

void	parse_command(char *cmd, char **envp, char **cmd_path, char ***cmd_args)
{
	*cmd_args = ft_split(cmd, ' ');
	if (!*cmd_args || !(*cmd_args)[0])
	{
		perror("parse_command");
		exit(127);
	}
	*cmd_path = find_path((*cmd_args)[0], envp);
	if (!*cmd_path)
	{
		perror("command not found");
		exit(127);
	}
}

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

pid_t run_commands(t_data *data, int prev_fd, int start_index)
{
	int     fd[2];
	int     i;
	pid_t   last_pid;
	t_cmd   cmd;

	i = start_index;
	while (i < data->argc - 2)
	{
		if (pipe(fd) == -1)
		{
			perror("pipe");
			exit(1);
		}
		cmd.args = ft_split(data->argv[i], ' ');
		cmd.path = find_path(cmd.args[0], data->envp);
		cmd.envp = data->envp;
		exec_middle(prev_fd, &cmd, fd);
		free(cmd.path);
		ft_free_tab(cmd.args);
		close(prev_fd);
		close(fd[1]);
		prev_fd = fd[0];
		i++;
	}
	cmd.args = ft_split(data->argv[data->argc - 2], ' ');
	cmd.path = find_path(cmd.args[0], data->envp);
	cmd.envp = data->envp;
	last_pid = exec_last(prev_fd, &cmd, data);
	free(cmd.path);
	ft_free_tab(cmd.args);
	close(prev_fd);
	return (last_pid);
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

	last_pid = run_commands(&data, prev_fd, 3);
	return (wait_all(last_pid));
}
