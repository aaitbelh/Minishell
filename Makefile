Name = minishell

LIBFT = libft/libft.a 

SRCS = main.c src/tools.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

all : $(Name)

$(Name): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L/Users/aaitbelh/.brew/opt/readline/lib -I/Users/aaitbelh/.brew/opt/readline/include  $(LIBFT) -o $(Name)

clean :
	make -C libft clean
	rm -rf $(OBJS)

fclean : clean
	make -C libft fclean
	rm -rf $(Name)

re : fclean all