/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/29 15:54:58 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_print_it(char **str, int i)
{
	while (str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if (str[i + 1])
			write(1, " ", 1);
		i++;
	}
}

void	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	printf("%s\n", path);
	free(path);
}

void	ft_echo(char **str)
{
	int	i;
	int	j;

	i = 0;
	while (str[i] && str[i + 1] && ft_strlen(str[0]) != 1)
	{
		j = 1;
		while (str[i][j])
		{
			if (str[i][0] != '-' || str[i][j] != 'n')
				break ;
			j++;
		}
		if (str[i][j])
			break ;
		i++;
	}
	j = i;
	ft_print_it(str, i);
	if (j == 0)
		write(1 , "\n", 1);
}

void	ft_cd(char *path)
{
	int		ret;
	char	*env;

	if (!path)
	{
		edit_oldpwd();
		env = get_from_env("HOME=", 5, 5);
		if (ft_strlen("HOME=") != ft_strlen(env))
			ret = chdir(env);
		if (ENOENT == errno)
			ft_join_error("Minishell: cd:", path,  1);
		else if (ret < 0)
			ft_error_ret("Minishell : cd : HOME not set \n", 1);
		edit_pwd();
		free(env);
	}
	else
		go_to_env(path);
	free(path);
}
