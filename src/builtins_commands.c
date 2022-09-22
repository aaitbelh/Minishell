/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casper <casper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/09/22 11:05:52 by casper           ###   ########.fr       */
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
	int			i;

	path = getcwd(NULL, 0);
	if(path)
	{
		free(g_data.old_path);
		g_data.old_path = ft_strdup(path);
	}
	printf("%s\n", g_data.old_path);
	free(path);
}

void	ft_echo(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		j = 0;
		if (str[i][j] == '-' && str[i][j + 1])
			while(str[i][++j] == 'n')
				if(str[i][j] != 'n')
					break;
		if(str[i][j])
			break;
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
		free(env);
	}
	else
		go_to_env(path);
}
