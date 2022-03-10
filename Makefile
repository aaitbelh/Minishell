Name = minishell

SRCS = main.c src/tools.c

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra 

all : $(Name)

$(Name): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -lreadline -L/Users/alaajili/.brew/opt/readline/lib -I/Users/alaajili/.brew/opt/readline/include -o $(Name)

clean :
	rm -f $(OBJS)

fclean : clean
	rm -f $(Name)

re : fclean all