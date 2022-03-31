Name = minishell
LIBFT = libft/libft.a
SRCS = main.c srcs/tools0.c srcs/tools.c srcs/tools2.c srcs/tools3.c srcs/tools4.c
OBJS = $(SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Werror -Wextra
READLINE = -lreadline -L/Users/alaajili/.brew/opt/readline/lib -I/Users/alaajili/.brew/opt/readline/include
SANITIZE = -fsanitize=address

all : $(Name)

$(Name): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(LIBFT) $(OBJS) $(READLINE) -o $(Name) $(SANITIZE)

clean :
	make -C libft clean
	rm -f $(OBJS)

fclean : clean
	make -C libft fclean
	rm -f $(Name)

re : fclean all