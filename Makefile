NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS = pipex.c \
		ft_utils.c \
		ft_cmd1.c \
		ft_cmd2.c \
		ft_printf/ft_addr.c \
		ft_printf/ft_auxilliere1.c \
		ft_printf/ft_auxilliere2.c \
		ft_printf/ft_hexa_unsigned.c \
		ft_printf/ft_printf.c \
		ft_printf/ft_put.c \
		ft_printf/ft_putnbr.c \
		ft_printf/ft_putstr.c \
		ft_path.c \
		ft_split.c
OBJS = $(SRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS)
	cc $(CFLAGS) -o $(NAME) $(OBJS)


%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(NAME)

re : fclean all

