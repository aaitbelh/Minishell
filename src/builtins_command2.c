/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:46:37 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/30 15:45:01 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	go_to_env(char *path)
{
	int	ret;
	
	edit_oldpwd();
	ret = chdir(path);
	if (ENOENT == errno)
		ft_join_error("Minishell : cd:", path, 1);
	else if (ret < 0)
		ft_join_error("Minishell : cd:", path, 1);
	edit_pwd();
}

int ft_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if(!cmd->arg[0])
	{
		write(1,"exit\n", ft_strlen("exit\n"));
		exit(0);
	}
	if(!check_allnum(cmd->arg[0]))
	{
		write(1,"exit\n", ft_strlen("exit\n"));
		join_th_errors("minishell: exit: ", cmd->arg[0], ": numeric argument required 1", 255);
	}
	while(cmd->arg[i])
		i++;
	if(i != 1)
		return (ft_error_ret("minishell : exit: too many arguments", 1));
	else
	{
		write(1,"exit\n", ft_strlen("exit\n"));
		if(ft_atoi(cmd->arg[0]) >= 0 && ft_atoi(cmd->arg[0]) <= 9223372036854775807L)
			exit(ft_atoi(cmd->arg[0]) % 256);
		else if(ft_atoi(cmd->arg[0]) < 0 && (long)ft_atoi(cmd->arg[0]) >= (-9223372036854775807 - 1))
			exit(atoi(cmd->arg[0]) % 256 + 256);
	}
	return (1);
}