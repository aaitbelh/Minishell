/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:11:28 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/31 16:13:50 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <string.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <signal.h>
#include <stdlib.h>
#include <fcntl.h>
#include <errno.h>
#include "../libft/libft.h"



# define IN 0
# define OUT 1
# define HERDOC 2
# define APPOUT 3

struct s_data g_data;



typedef struct s_file
{
	char	*file_name;
	int		file_type;
}	t_file;

typedef struct s_cmd
{
	char	*command;
	int		p_herdoc;
	char	**arg;
	t_file	*file;
	char **ev;
}	t_cmd;

typedef struct s_data
{
	char **ev;
	int	n;
	char **exp;
	int *pipe;
	int input;
	int output;
	int	x;	
	struct sigaction	sa;
	int					*num_of_files;
	int					word_len;
	int					*num_of_args;
	char				*line;
	char				*word;
	char				**cmds;
	struct sigaction	sb;
	struct s_cmd *cmd;
}	t_data;

char	**cpy_env(char **str);
void	rl_replace_line (char *text, int clear_undo);
void	handler(int sig);
void	ft_error_ex(char *str, int Exit);
int		is_there_space(char *str);
char	*get_from_env(char *str, int size, int start);
int		ft_join_error(char *s1, char *s2, int Exit);
void	ft_error_fd(char *str, int Exit);
void	edit_oldpwd();
void	ft_cd(char *path);
void	ft_pwd();
void	ft_echo(char **str);
int		ft_error_ret(char *str, int ret);
int		ret_indice_env(char **env, char *str);
void	edit_pwd();
char	**cpy_exp(char **env);
void	sort_it(char **table);
void	ft_strswap(char **s1, char **s2);
int		ft_export(char **path);
int		syntax_check(char *str);
void	add_bath_evx(char *str);
char	**add_new(char *str);
void	twoDfree(char **table);
char	**delete_it(int ind);
void	unset(char **str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		is_command(t_cmd *cmd, int i);
char	*ft_check_acs(char **env, char *cmd);
char	**fix_command(char *cmd, char **args);
int		is_there_herdoc();
int		ft_exit(t_cmd *cmd);
int		join_th_errors(char *s1, char *s2, char *s3, int Exit);
int		check_allnum(char *str);
int		wh_typeit(t_cmd *cmd, int i);
void	go_to_env(char *path);
void	ft_print_it(char **str, int i);
void	red_files(t_cmd *cmd, int i);

# endif