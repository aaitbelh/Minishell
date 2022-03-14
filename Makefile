Name = minishell

SRCS = main.c srcs/tools.c srcs/ft_split.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

SANITIZE = -fsanitize=address

all : $(Name)

$(Name): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L/Users/alaajili/.brew/opt/readline/lib -I/Users/alaajili/.brew/opt/readline/include -o $(Name) $(SANITIZE)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -rf $(Name)

re : fclean all