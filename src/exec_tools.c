/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 17:22:21 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/07 23:38:03 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	the_exit_code(void)
{
	if (WIFSIGNALED(g_data.ret))
		g_data.ret = 130;
	else
		g_data.ret = WEXITSTATUS(g_data.ret);
	free(g_data.pipe);
	free(g_data.pid);
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
	rl_replace_line("", 0);
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
	g_data.out = dup(1);
	g_data.in = dup(0);
	red_files(cmd, 0);
}
