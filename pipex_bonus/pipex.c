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

void	exec_commande(char *cmd, char **envp)
{
	char	**split;
	char	*path;

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
	execve(path, split, envp);
	perror("execve fail");
	ft_free_tab(split);
	free(path);
	exit(EXIT_FAILURE);
}



int	main(int argc, char **argv, char **envp)
{
	if (argc < 5)
		return (error_msg("error argument :( "));
	if (ft_strcmp(argv[1], "here_doc") == 0)
		return (here_doc(argc, argv, envp));
	else
		return (pipex(argc, argv, envp));
}
