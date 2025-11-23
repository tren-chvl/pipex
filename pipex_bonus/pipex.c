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

void	parse_command(char *cmd, char **envp, char **cmd_path, char ***cmd_args)
{
	*cmd_args = ft_split(cmd, ' ');
	if (!*cmd_args || !(*cmd_args)[0])
	{
		perror("parse_command");
		exit(127);
	}
	*cmd_path = find_path((*cmd_args)[0], envp);
	if (!*cmd_path)
	{
		perror("command not found");
		exit(127);
	}
}

void safe_execve(char *path, char **argv, char **envp)
{
	if (!path) 
	{
		ft_free_tab(argv);
		exit(127);
	}

	execve(path, argv, envp);
	ft_free_tab(argv);
    free(path);
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
	if (!cmd || !*cmd)
		exit(127);
	char **split;
	char *path;

	split = ft_split(cmd, ' ');
	if (!split || !split[0] || !*split[0]) 
	{
		ft_free_tab(split);
		exit(127);
	}
	if (ft_strchr(split[0], '/'))
		path = ft_strdup(split[0]);
	else
		path = find_path(split[0], envp);

	safe_execve(path, split, envp);
}

int main(int argc, char **argv, char **envp)
{
	int ret;

	if (argc < 5)
		return (error_msg("error argument :( "));
	if (ft_strcmp(argv[1], "here_doc") == 0)
		ret = here_doc(argc, argv, envp);
	else
		ret = pipex(argc, argv, envp);
	return (ret);
}
