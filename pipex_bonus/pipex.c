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

void safe_execve(char *path, char **argv, char **envp)
{
    if (!path) 
	{
        ft_free_tab(argv);
        exit(127); // commande introuvable
    }
    char *tmp_path = path;
    char **tmp_argv = argv;

    execve(tmp_path, tmp_argv, envp);
    ft_free_tab(tmp_argv);
    free(tmp_path);

    if (errno == EACCES)
        exit(126);
    else if (errno == ENOENT) 
	{
        if (ft_strchr(argv[0], '/'))
            exit(1);
        else
            exit(127);
    } else 
	{
        perror("execve");
        exit(1);
    }
}

void exec_commande(char *cmd, char **envp)
{
    char **split = ft_split(cmd, ' ');
    char *path;

    if (!split || !split[0] || !*split[0]) 
	{
        safe_execve(NULL, split, envp); // laisse safe_execve gérer
    }

    if (ft_strchr(split[0], '/'))
        path = ft_strdup(split[0]); // chemin explicite
    else
        path = find_path(split[0], envp); // recherche dans PATH

    safe_execve(path, split, envp);
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

