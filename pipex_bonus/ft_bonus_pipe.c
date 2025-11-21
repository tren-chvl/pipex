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

pid_t exec_last(int prev_fd, char *cmd_path, char **cmd_args, char **envp, t_data *data)
{
    int outfile_fd;
    pid_t pid;

    outfile_fd = open(data->outfile_path,
                      O_WRONLY | O_CREAT | (data->append ? O_APPEND : O_TRUNC),
                      0644);
    if (outfile_fd == -1)
    {
        perror("open outfile");
        exit(1);
    }
    pid = fork();
    if (pid == -1)
    {
        perror("fork");
        exit(1);
    }
    if (pid == 0)
    {
        dup2(prev_fd, STDIN_FILENO);
        dup2(outfile_fd, STDOUT_FILENO);
        close(prev_fd);
        close(outfile_fd);
        safe_execve(cmd_path, cmd_args, envp);
    }
    close(outfile_fd);
    return pid;
}

pid_t exec_middle(int prev_fd, char *cmd_path, char **cmd_args, char **envp, int fd[2])
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
        safe_execve(cmd_path, cmd_args, envp);
    }
    return pid;
}


int pipex(int argc, char **argv, char **envp)
{
    t_data  data;
    int     infile;
    int     prev_fd;
    int     i;
    pid_t   last_pid;
    char    *cmd_path;
    char    **cmd_args;
    int     fd[2];
	int exit_code;

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
        {
            perror("pipe");
            exit(1);
        }
        cmd_args = ft_split(argv[i], ' ');
        cmd_path = find_path(cmd_args[0], envp);
        exec_middle(prev_fd, cmd_path, cmd_args, envp, fd);
        free(cmd_path);
        ft_free_tab(cmd_args);
        close(prev_fd);
        close(fd[1]);
        prev_fd = fd[0];
        i++;
    }
    cmd_args = ft_split(argv[argc - 2], ' ');
    cmd_path = find_path(cmd_args[0], envp);
    last_pid = exec_last(prev_fd, cmd_path, cmd_args, envp, &data);
    free(cmd_path);
    ft_free_tab(cmd_args);
    close(prev_fd);
    exit_code = wait_all(last_pid);
    exit(exit_code);
}



