/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:21 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/19 10:58:24 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	exec_commande(char *cmd, char **envp)
{
	char	**split;
	char	*path;

	if (!cmd || cmd[0] == '\0')
	{
		write(2, "pipex: command not found\n", 25);
		exit(127);
	}
	split = ft_split(cmd, ' ');
	if (!split)
		exit(EXIT_FAILURE);
	path = find_path(split[0], envp);
	if (!path)
	{
		ft_free_tab(split);
		write(2, "pipex: command not found\n", 25);
		exit(127);
	}
	execve(path, split, envp);
	perror("execve");
	ft_free_tab(split);
	free(path);
	if (errno == EACCES)
		exit(126);
	exit(127);
}

int	main(int argc, char *argv[], char **envp)
{
	int		fd[2];
	int		status;
	t_pid	pid;

	if (argc != 5)
		return (perror("error argument :( "), EXIT_FAILURE);
	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid.pid1 = fork();
	if (pid.pid1 == -1)
		return (error_msg("fork"));
	if (pid.pid1 == 0)
		procces_child1(fd, argv, envp);
	pid.pid2 = fork();
	if (pid.pid2 == -1)
		return (error_msg("fork"));
	if (pid.pid2 == 0)
		procces_child2(fd, argv, envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid.pid1, NULL, 0);
	waitpid(pid.pid2, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (0);
}
