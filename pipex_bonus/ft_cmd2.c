/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cmd2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:51 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/18 15:28:29 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void procces_child2(int *fd, char **argv,char **envp)
{
	int outfile;

	outfile = open(argv[4], O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (outfile == -1)
		exit(error_msg("outfile"));
	dup2(fd[0],STDIN_FILENO);
	dup2(outfile,STDOUT_FILENO);
	close(outfile);
	close(fd[0]);
	close(fd[1]);
	exec_commande(argv[3],envp);
}
