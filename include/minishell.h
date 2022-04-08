/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:11:28 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/07 23:35:57 by aaitbelh         ###   ########.fr       */
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
# include <fcntl.h>
# include <errno.h>
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
	int		p_herdoc;
	char	**arg;
	t_file	*file;
}	t_cmd;

typedef struct s_data
{
	char				**ev;
	int					n;
	char				**exp;
	int					input;
	int					output;
	int					in;
	int					out;
	int					x;
	struct sigaction	sa;
	int					*num_of_files;
	int					word_len;
	int					*num_of_args;
	char				*line;
	char				*word;
	char				**cmds;
	char				*t;
	struct sigaction	sb;
	int					ret;
	int					*pid;
	int					*pipe;
	struct s_cmd		*cmd;
	int					index;
}	t_data;

char	**cpy_env(char **str);
void	rl_replace_line(char *text, int clear_undo);
void	handler(int sig);
void	ft_error_ex(char *str, int Exit);
int		is_there_space(char *str);
char	*get_from_env(char *str, int size, int start);
int		ft_join_error(char *s1, char *s2, int Exit);
void	ft_error_fd(char *str, int Exit);
void	edit_oldpwd(void);
void	ft_cd(char *path);
void	ft_pwd(void);
void	ft_echo(char **str);
int		ft_error_ret(char *str, int ret);
int		ret_indice_env(char **env, char *str);
void	edit_pwd(void);
char	**cpy_exp(char **env);
void	sort_it(char **table);
void	ft_strswap(char **s1, char **s2);
int		ft_export(char **path);
int		syntax_check(char *str);
void	add_bath_evx(char *str);
char	**add_new(char *str);
void	twodfree(char **table);
char	**delete_it(int ind);
void	unset(char **str);
char	*ft_strjoin_gnl(char *s1, char *s2);
int		is_command(t_cmd *cmd, int i);
char	*ft_check_acs(char **env, char *cmd);
char	**fix_command(char *cmd, char **args);
int		is_there_herdoc(void);
int		ft_exit(t_cmd *cmd);
int		join_th_errors(char *s1, char *s2, char *s3, int Exit);
int		check_allnum(char *str);
int		wh_typeit(t_cmd *cmd);
void	go_to_env(char *path);
void	ft_print_it(char **str, int i);
void	red_files(t_cmd *cmd, int i);
void	is_builtins(t_cmd *cmd);
void	start_exec(void);
void	is_builtins(t_cmd *cmd);
void	handler_2(int sig);
void	handler(int sig);
int		wh_typeit(t_cmd *cmd);
void	red_in_main(t_cmd *cmd);
void	error_norm(char *str);
int		join_th_errors_re(char *s1, char *s2, char *s3, int ret);
void	the_exit_code(void);
void	declared_all(void);
void	print_the_env(void);
void	print_the_exp(void);
void	free_all_structs(void);
//---------------------
void	get_command(int k, int j, int i);
int		get_num_of_args_files(int i, int k);
void	get_args_files(int i, int k, int a, int b);
int		skip_quotes(int i, int k);
int		get_num_of_args_files_2(int i, int k);
void	get_args_files_2(int i, int j, int k);
int		check_error(int i, int k);
int		check_error_2(int i, int k);
int		get_file_type(int i, int k, int b);
int		check_len(int i, int k);
void	cpy_file_name(int i, int k, int j, int b);
void	get_cmds(char *line, int x);
int		without_qoutes(int i, int j, int k);
int		double_qoutes(int i, int j);
int		single_qoutes(int i, int j);
int		handle_env_var(int i, int j);
int		handle_cmds(void);

#endif