/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:46:37 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/28 18:15:45 by aaitbelh         ###   ########.fr       */
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
	i = 1;

	if(!cmd->arg[0])
		exit(0);
	if(check_allnum(cmd->arg[0]))
		exit(join_th_errors("minishell: exit: ", cmd->arg[0], "numeric argument required", 255));
	while(cmd->arg[i])
		i++;
	if(i != 1)
		return (ft_error_ret("minishell : exit: too many arguments", 1));
	else
	{
		if(ft_atoi(cmd->arg[0]) > 0 && ft_atoi(cmd->arg[0]) < (int)9223372036854775807L)
			exit(ft_atoi(cmd->arg[0]) % 256);
		else if(ft_atoi(cmd->arg[0]) > (int)9223372036854775807L)
		{
			join_th_errors("minishell: exit: ", cmd->arg[0], "numeric argument required", 1);
			exit(256 % atoi(cmd->arg[0]));
		}
		else if(ft_atoi(cmd->arg[0]) < 0 && ft_atoi(cmd->arg[0]) > (int )(-9223372036854775807) - 1)
		{
			join_th_errors("minishell: exit: ", cmd->arg[0], "numeric argument required", 1);
			exit(atoi(cmd->arg[0]) % 256 + 256);
		}
		else
		{
			join_th_errors("minishell: exit: ", cmd->arg[0], "numeric argument required", 1);
			exit(1);
		}
	}
	return (1);
}