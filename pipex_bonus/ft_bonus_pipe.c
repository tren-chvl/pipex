#include "pipex.h"



void exec_middle(int prev_fd, char *cmd, char **envp, int *fd)
{
    if (fork() == 0)
    {
        dup2(prev_fd, STDIN_FILENO);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[0]);
        exec_cmd(cmd, envp);
    }
    close(fd[1]);
    if (prev_fd != -1)
        close(prev_fd);
}

void exec_last(int prev_fd, int outfile, char *cmd, char **envp)
{
    if (fork() == 0)
    {
        dup2(prev_fd, STDIN_FILENO);
        dup2(outfile, STDOUT_FILENO);
        exec_cmd(cmd, envp);
    }
    close(prev_fd);
    close(outfile);
}

int pipex(int argc, char **argv, char **envp)
{
    int infile;
    int outfile;
    int fd[2];
    int prev_fd;
    int i;

    infile = open(argv[1], O_RDONLY);
    if (infile < 0)
        return (perror("infile"), 1);
    outfile = open(argv[argc - 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (outfile < 0)
        return (perror("outfile"), 1);
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
    exec_last(prev_fd, outfile, argv[argc - 2], envp);
    wait_all();
    return (0);
}


