/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:11:28 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/31 12:43:40 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include "../libft/libft.h"

# define IN 0
# define OUT 1
# define HERDOC 2
# define APPOUT 3

struct s_data	g_data;

typedef struct s_file
{
	char	*file_name;
	int		file_type;
}	t_file;

typedef struct s_cmd
{
	char	*command;
	char	**arg;
	t_file	*file;
}	t_cmd;

typedef struct s_data
{
	char				**ev;
	char				**cmds;
	char				*word;
	char				*line;
	int					word_len;
	int					*num_of_args;
	int					*num_of_files;
	int					x;
	struct sigaction	sa;
	struct sigaction	sb;
	struct s_cmd		*cmd;
}	t_data;

char	**cpy_env(char **str);
void	rl_replace_line(char *text, int clear_undo);
void	get_command(int k, int j, int i);
void	get_num_of_args_files(int i, int k);
void	get_args_files(int i, int k, int b);
int		skip_quotes(int i, int k);
int		get_num_of_args_files_2(int i, int k);
void	get_args_files_2(int i, int j, int k);
int		check_error(int i, int k);
int		check_error_2(int i, int k);
int		get_file_type(int i, int k, int b);
int		check_len(int i, int k);
void	cpy_file_name(int i, int k, int j, int b);
void	handler(int sig);
void	get_cmds(char *line, int x);

#endif