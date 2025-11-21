/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bonus_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 14:51:03 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 16:49:58 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void exec_middle(int prev_fd, char *cmd, char **envp, int *fd)
{
	if (fork() == 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);
		close(prev_fd);
		close(fd[0]);
		close(fd[1]);
		exec_commande(cmd, envp);
		perror("exec_commande");
		exit(1);
	}
	close(fd[1]);
	if (prev_fd != -1)
		close(prev_fd);
}

pid_t exec_last(int prev_fd, char *cmd, char **envp, t_data *data)
{
    pid_t pid;
    int outfile;
    int flags;

    flags = O_WRONLY | O_CREAT | (data->append ? O_APPEND : O_TRUNC);
    outfile = open(data->outfile_path, flags, 0644);
    if (outfile < 0)
    {
        perror("outfile");
        exit(1);
    }

    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }

    if (pid == 0) // 👈 Ici ton bloc
    {
        printf("DEBUG: exec_last child pid=%d\n", getpid());

        if (dup2(prev_fd, STDIN_FILENO) == -1)
            exit(1);
        if (dup2(outfile, STDOUT_FILENO) == -1)
            exit(1);

        close(prev_fd);
        close(outfile);

        exec_commande(cmd, envp);

        // si exec_commande retourne au lieu de faire execve
        printf("DEBUG: exec_commande returned in pid=%d\n", getpid());
        exit(1);
    }

    printf("DEBUG: exec_last forked pid=%d\n", pid);
    close(prev_fd);
    close(outfile);
    return pid;
}



int pipex(int argc, char **argv, char **envp)
{
	t_data  data;
	int     infile;
	int     fd[2];
	int     prev_fd;
	int     i;
	pid_t last_pid;

	data.argc = argc;
	data.argv = argv;
	data.envp = envp;
	data.outfile_path = argv[argc - 1];
	data.append = 0;
	infile = open(argv[1], O_RDONLY);
	if (infile < 0)
		return (perror("infile"), 1);
	prev_fd = infile;
	i = 2;
	while (i < argc - 2)
	{
		if (pipe(fd) == -1)
			return (perror("pipe"), 1);
		exec_middle(prev_fd, argv[i], envp, fd);
		prev_fd = fd[0];
		i++;
	}
	last_pid = exec_last(prev_fd, argv[argc - 2], envp, &data);
	wait_all(last_pid);
	return (0);
}
