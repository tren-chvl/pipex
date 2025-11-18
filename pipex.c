/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:21 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/18 15:55:38 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exec_commande(char *cmd ,char **envp)
{
	char **split;
	char *path;

	split = ft_split(cmd, ' ');
	if (!split)
		exit(EXIT_FAILURE);
	path = find_path(split[0], envp);
	if (!path)
	{
		ft_free_tab(split);
		perror("command not found");
		exit(EXIT_FAILURE);
	}
	execve(path,split,envp);
	perror("execve fail");
	ft_free_tab(split);
	free(path);
	exit(EXIT_FAILURE);
}

int main(int argc,char *argv[],char **envp)
{
	int fd[2];
	pid_t pid1;
	pid_t pid2;

	if (argc != 5)
		return(perror("error argument :( "),EXIT_FAILURE);
	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid1 = fork();
	if (pid1 == -1)
		return (error_msg("fork"));
	if (pid1  == 0)
		procces_child1(fd,argv,envp);
	pid2 = fork();
	if (pid2 == -1)
		return (error_msg("fork"));
	if (pid2  == 0)
		procces_child2(fd,argv,envp);
	close(fd[0]);
	close(fd[1]);
	waitpid(pid1, NULL,0);
	waitpid(pid2,NULL,0);
	return (0);
}
