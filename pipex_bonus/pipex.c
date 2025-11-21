/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:21 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 17:04:23 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <string.h>

#include "pipex.h"
#include <errno.h>
#include <string.h>
#include <stdio.h>


void exec_commande(char *cmd, char **envp)
{
    char **split;
    char *path;

    printf("DEBUG: exec_commande running in pid=%d\n", getpid());
    split = ft_split(cmd, ' ');
    if (!split)
    {
        perror("malloc");
        exit(1);
    }
    path = find_path(split[0], envp);
    if (!path)
    {
        ft_free_tab(split);
        fprintf(stderr, "DEBUG: path=NULL, exit(127) pid=%d\n", getpid());
        exit(127);
    }
    execve(path, split, envp);
    perror("execve");
    ft_free_tab(split);
    free(path);
    fprintf(stderr, "DEBUG errno=%d (%s) pid=%d\n",
            errno, strerror(errno), getpid());
    if (errno == ENOENT)
        exit(127);
    else if (errno == EACCES)
        exit(126);
    else
        exit(1);
}



int main(int argc, char **argv, char **envp)
{
    if (argc < 5)
        return (error_msg("error argument :( "));
    if (ft_strcmp(argv[1], "here_doc") == 0)
        here_doc(argc, argv, envp);
    else
        pipex(argc, argv, envp);
    return 0;
}


