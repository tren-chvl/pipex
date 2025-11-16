#ifndef PIPEX_H
#define PIPEX_H

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
# include <errno.h>
# include <stdarg.h>
# include <stdio.h>


int    error_msg(char *msg);
char *ft_strjoin(char *dir, char *cmd);
int ft_strlen(char *str);
char **ft_split(char const *s, char c);
int	ft_strncmp(char *s1, char *s2, unsigned int n);

char *find_path(char *cmd, char **envp);


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