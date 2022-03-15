/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_commands.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/15 11:38:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/15 18:19:21 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


void ft_echo(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while(str[i] && ft_strlen(str[0]) != 1)
	{
		j = 1;
		while(str[i][j])
		{
			if(str[i][0] != '-' || str[i][j] != 'n')
					break ;
			j++;
		}
		if(str[i][j])
			break;
		i++;
	}
	j = i;
	while(str[i])
	{
		write(1, str[i], ft_strlen(str[i]));
		if(str[i + 1])
			write(1, " ", 1);
		i++;
	}
	if(j == 0)
		write(1 ,"\n", 1);
}

void ft_cd(char **path)
{
	int		ret;
	char	*old_pwd;
	char	*env;

	old_pwd = getcwd(NULL, 0);
	if(!*path[1])
	{
		env = get_from_env("HOME=", 5, 5);
		ret = chdir(env);
		if(NULL)
			ft_join_error("Minishell : cd : HOME not set \n", "", 1);
	}
	else
	{
		ret = chdir(path[1]);
		if(ENOENT == errno)
			ft_join_error("Minishell : cd:", path[1], 1);
		else if(ret < 0)
			ft_join_error("Minishell : cd:", path[1], 1);
	}
}

