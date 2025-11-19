/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:30 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/19 10:59:57 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <stdarg.h>
# include <stdio.h>


typedef struct s_pid
{
    pid_t pid1;
    pid_t pid2;
}   t_pid;

int		error_msg(char *msg);
char	*ft_strjoin(char *dir, char *cmd);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

void	procces_child2(int *fd, char **argv, char **envp);
void	procces_child1(int *fd, char **argv, char **envp);

char	*find_path(char *cmd, char **envp);
void	ft_free_tab(char **tab);
void	exec_commande(char *cmd, char **envp);

#endif