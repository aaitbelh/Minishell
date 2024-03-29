/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casper <casper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:22:21 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/09/22 10:31:30 by casper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	the_exit_code(void)
{
	if (WIFSIGNALED(g_data.ret))
		g_data.ret = 130;
	else
		g_data.ret = WEXITSTATUS(g_data.ret);
	if (g_data.x != 0)
		free(g_data.pipe);
}

void	handler_2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

void	handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_redisplay();
}

int	wh_typeit(t_cmd *cmd)
{
	if (!cmd->command)
		return (0);
	if (!strcmp(cmd->command, "cd") || !strcmp(cmd->command, "pwd")
		|| !strcmp(cmd->command, "echo") || !strcmp(cmd->command, "export")
		|| !strcmp(cmd->command, "unset") ||!strcmp(cmd->command, "exit")
		|| !strcmp(cmd->command, "env"))
		return (1);
	return (0);
}

void	red_in_main(t_cmd *cmd)
{
	if (g_data.num_of_files[0] != 0)
	{
		g_data.out = dup(1);
		g_data.in = dup(0);
		if (!red_files1(cmd, 0))
			is_builtins(cmd);
		dup2(g_data.out, 1);
		dup2(g_data.in, 0);
	}
	else
		is_builtins(cmd);
}
