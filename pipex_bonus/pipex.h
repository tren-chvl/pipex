/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:30 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/20 12:55:01 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10000
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_data
{
    int		argc;
    char	**argv;
    char	**envp;
    char	*outfile_path;
    int		append;
}   t_data;

typedef struct s_file
{
	int outfile;
	int flags;
	pid_t pid;
}	t_file;

void    safe_execve(char *path, char **argv, char **envp);
int		error_msg(char *msg);
char	*ft_strjoin(char *dir, char *cmd);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);
int		ft_strcmp(char *s1, char *s2);
void	ft_bzero(void *s, size_t n);
void	procces_child2(int *fd, char **argv, char **envp);
void	procces_child1(int *fd, char **argv, char **envp);

char	*find_path(char *cmd, char **envp);
void	ft_free_tab(char **tab);
void	exec_commande(char *cmd, char **envp);
int		here_doc(int argc, char **argv, char **envp);
int		pipex(int argc, char **argv, char **envp);
int     wait_all(pid_t last_pid);
pid_t   exec_middle(int prev_fd, char *cmd_path, char **cmd_args, char **envp, int fd[2]);
pid_t   exec_last(int prev_fd, char *cmd_path, char **cmd_args, char **envp, t_data *data);

char	*get_next_line(int fd);
char	*read_newline(int fd, char *line);
char	*extract_line(char *line);
char	*clean_line(char *line);

size_t	ft_strlen_g(char *line);
char	*ft_strjoin_gnl(char *s1, char *s2);
char	*ft_strchr(char *s, int c);
char	*free_return(char *s1, char *join);
char    *ft_strdup(char *s1);
char	*null_free(char **tab);
char	*full_free(char **tab, char *full);

#endif