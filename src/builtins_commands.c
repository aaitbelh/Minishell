/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/08 01:03:58 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_print_it(char **str, int i)
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
	while (str[i] && ft_strlen(str[0]) != 1)
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
		write(1, "\n", 1);
}

void	ft_cd(char *path)
{
	char	*env;

	if (!path)
	{
		edit_oldpwd();
		env = get_from_env("HOME=", 5, 5);
		if (!env)
		{
			ft_error_ret("Minishell : cd: HOME not set", 1);
			return ;
		}
		if (env && !env[0])
		{
			chdir(".");
			return ;
		}
		if (env && ft_strlen("HOME=") != ft_strlen(env))
			go_to_env(env);
		edit_pwd();
		free(env);
	}
	else
		go_to_env(path);
}
