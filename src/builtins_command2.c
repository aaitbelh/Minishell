/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_command2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casper <casper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/25 21:46:37 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/15 19:06:18 by casper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exit_norm(t_cmd *cmd)
{
	write(1, "exit\n", ft_strlen("exit\n"));
	if (ft_atoi(cmd->arg[0]) >= 0
		&& ft_atoi(cmd->arg[0]) <= 9223372036854775807L)
		exit(ft_atoi(cmd->arg[0]) % 256);
	else if (ft_atoi(cmd->arg[0]) < 0
		&& (long)ft_atoi(cmd->arg[0]) >= (-9223372036854775807 - 1))
		exit(atoi(cmd->arg[0]) % 256 + 256);
}

void	go_to_env(char *path)
{
	int	ret;

	edit_oldpwd();
	ret = chdir(path);
	if (ENOENT == errno)
		join_error("Minishell : cd: ", path, 1);
	if (ret < 0)
		join_error("Minishell : cd: ", path, 1);
	edit_pwd();

}

int	ft_exit(t_cmd *cmd)
{
	int	i;

	i = 0;
	if (!cmd->arg[0])
	{
		write(1, "exit\n", ft_strlen("exit\n"));
		exit(0);
	}
	if (!check_allnum(cmd->arg[0]))
	{
		write(1, "exit\n", ft_strlen("exit\n"));
		join_th_errors("minishell: exit: ", cmd->arg[0],
			": numeric argument required", 255);
	}
	while (cmd->arg[i])
		i++;
	if (i != 1)
		return (ft_error_ret("minishell : exit: too many arguments", 1));
	else
		exit_norm(cmd);
	return (1);
}
