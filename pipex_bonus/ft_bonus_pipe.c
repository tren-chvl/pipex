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
