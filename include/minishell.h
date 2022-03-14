/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:11:28 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/14 20:22:47 by alaajili         ###   ########.fr       */
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
	char	**arg;
	t_file	*file;
}	t_cmd;

typedef struct s_data
{
	char			**ev;
	char			**cmds;
	char			*word;
	int				word_len;
	struct s_cmd	*cmd;
}	t_data;

char	**cpy_env(char **str);
void	rl_replace_line (char *text, int clear_undo);
char	**ft_split(char const *s, char c);

#endif