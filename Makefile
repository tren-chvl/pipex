NAME = pipex
CC = gcc
CFLAGS = -Wall -Wextra -Werror
SRCS =	pipex.c \
		ft_utils.c \
		ft_cmd1.c \
		ft_cmd2.c \
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

