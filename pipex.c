/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:21 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/18 13:55:03 by marcheva         ###   ########.fr       */
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
	pid_t pid;

	if (argc != 5)
	{
		perror("");
		exit(EXIT_FAILURE);
	}
	if (pipe(fd) == -1)
		return (error_msg("pipe"));
	pid = fork();
	if (pid == -1)
		return (error_msg("fork"));
	if (pid == 0)
		procces_child(fd,argv,envp);
	else
	{
		procces_parent(fd,argv,envp);
		wait(NULL);
	}
	return (0);
}

// int main(int argc, char* argv[], char* envp[])
// {
//     for(int i = 0; envp[i] != NULL; i++)
//     {
//         printf("envp[%d] = %s\n", i, envp[i]);
//     }
 
//     return EXIT_SUCCESS;
// }
