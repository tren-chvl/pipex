/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:54 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:03 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int build_flags(t_data *data)
{
	int flags;

	flags = O_WRONLY | O_CREAT;
	if (data->append)
		flags |= O_APPEND;
	else
		flags |= O_TRUNC;
	return (flags);
}

int open_outfile(t_data *data)
{
	int fd;
	int flags;

	flags = build_flags(data);
	fd = open(data->outfile_path, flags, 0644);
	if (fd == -1)
	{
		perror("open outfile");
		exit(1);
	}
	return (fd);
}

void child_exec(int prev_fd, int outfile_fd, t_cmd *cmd)
{
	dup2(prev_fd, STDIN_FILENO);
	dup2(outfile_fd, STDOUT_FILENO);
	close(prev_fd);
	close(outfile_fd);
	safe_execve(cmd->path, cmd->args, cmd->envp);
}

pid_t exec_last(int prev_fd, t_cmd *cmd, t_data *data)
{
	int outfile_fd;
	pid_t pid;

	outfile_fd = open_outfile(data);
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
		child_exec(prev_fd, outfile_fd, cmd);
	close(outfile_fd);
	return (pid);
}
