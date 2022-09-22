Name = minishell

LIBFT = libft/libft.a 

SRCS = main.c src/exex_tools.c src/ft_errors.c src/builtins_commands.c src/more_tools.c src/edit_env.c src/utils.c src/export.c src/free_functions.c src/unset.c \
		src/execution_cmd.c src/get_cmdpath.c src/her_doc.c src/builtins_command2.c src/redc.files.c src/start_exec.c src/exec_tools.c src/tools0.c src/tools.c \
		src/tools2.c src/tools3.c src/tools4.c src/tools5.c src/tools6.c  src/tools7.c\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAGS = -g

all : $(Name)

$(Name): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(OBJS) -lreadline $(LIBFT) -o $(Name)

clean :
	make -C libft clean
	rm -rf $(OBJS)

fclean : clean
	make -C libft fclean
	rm -rf $(Name)

re : fclean all

t: $(Name)
	./$(Name)
