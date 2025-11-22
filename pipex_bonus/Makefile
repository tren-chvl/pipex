NAME = pipex
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRCS =	pipex.c \
		ft_utils.c \
		ft_cmd1.c \
		ft_cmd2.c \
		ft_path.c \
		ft_split.c \
		ft_bonus_pipe.c \
		ft_here_doc.c \
		get_next_line.c \
		get_next_line_utils.c \
		ft_utils2.c

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

.PHONY : re clean fclean all
