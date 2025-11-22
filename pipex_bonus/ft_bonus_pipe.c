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

pid_t exec_last(int prev_fd, t_cmd *cmd, t_data *data)
{
    int outfile_fd;
    int flags;
    pid_t pid;

    flags = O_WRONLY | O_CREAT;
    if (data->append)
        flags |= O_APPEND;
    else
        flags |= O_TRUNC;

    outfile_fd = open(data->outfile_path, flags, 0644);
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
        safe_execve(cmd->path, cmd->args, cmd->envp);
    }

    close(outfile_fd);
    return (pid);
}

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

int pipex(int argc, char **argv, char **envp)
{
    t_data  data;
    int     infile;
    int     prev_fd;
    pid_t   last_pid;
    int     exit_code;

    data.argc = argc;
    data.argv = argv;
    data.envp = envp;
    data.outfile_path = argv[argc - 1];
    data.append = 0;

    infile = open(argv[1], O_RDONLY);
    if (infile < 0)
        return (perror("infile"), 1);

    prev_fd = infile;
    last_pid = run_commands(&data, prev_fd, 2);
    exit_code = wait_all(last_pid);
    return (exit_code);
}
