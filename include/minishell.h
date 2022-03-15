/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 18:11:28 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/14 10:25:42 by aaitbelh         ###   ########.fr       */
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
#include "../libft/libft.h"

struct s_data g_data;

typedef struct s_data
{
	char **ev;
}	t_data;

char **cpy_env(char **str);
void rl_replace_line (char *text, int clear_undo);
void	handler(int sig);
void ft_error_fd(char *str, int Exit);
int	is_there_space(char *str);

# endif