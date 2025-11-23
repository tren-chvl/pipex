/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:51 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 11:22:17 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

pid_t exec_middle(int prev_fd, t_cmd *cmd, int fd[2])
{
	pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(1);
	}
	if (pid == 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(prev_fd);
		close(fd[0]);
		close(fd[1]);
		safe_execve(cmd->path, cmd->args, cmd->envp);
	}
	return (pid);
}
