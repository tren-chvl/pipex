/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marcheva <marcheva@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 10:06:30 by marcheva          #+#    #+#             */
/*   Updated: 2025/11/18 15:29:35 by marcheva         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
# include <sys/types.h>
# include <errno.h>
# include <stdarg.h>
# include <stdio.h>

typedef struct s_data
{
    int argc;
    char    **argv;
    char    **envp;
    int outfile;
}   t_data;


int		error_msg(char *msg);
char	*ft_strjoin(char *dir, char *cmd);
int		ft_strlen(char *str);
char	**ft_split(char *s, char c);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

void	procces_child2(int *fd, char **argv,char **envp);
void	procces_child1(int *fd,char **argv,char **envp);

char	*find_path(char *cmd, char **envp);
void    ft_free_tab(char **tab);
void	exec_commande(char *cmd ,char **envp);

int    ft_printf(const char *str, ...);
int    ft_putnbr(int nb);
int    ft_putstr(char *s);
int    ft_put(unsigned int nb);
int    ft_convert(unsigned long str);
int    ft_hexa_unsigned(unsigned int nb, int uppercase);
int    ft_addr(void *ptr);
int    ft_pourcentage(char c, va_list args);
int    pourcentage_c(va_list args);
int    pourcentage_double(void);
int    pourcentage_int(va_list args);
int    pourcentage_s(va_list args);
int    pourcentage_addr(va_list args);
int    pourcentage_u(va_list args);
int    pourcentage_x(va_list args, int uppercase);

#endif