/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 11:17:03 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/08 21:25:43 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_builtins(t_cmd *cmd)
{
	int	i;

	i = 0;
	g_data.ret = 0;
	if (!strcmp("cd", cmd->command))
		ft_cd(cmd->arg[0]);
	else if (!strcmp("pwd", cmd->command))
		ft_pwd();
	else if (!strcmp("echo", cmd->command))
		ft_echo(cmd->arg);
	else if (!strcmp("export", cmd->command))
		ft_export(cmd->arg);
	else if (!strcmp("unset", cmd->command))
		unset(cmd->arg);
	else if (!strcmp("exit", cmd->command))
		ft_exit(cmd);
	else if (!strcmp("env", cmd->command))
		print_the_env();
}

void	for_one_command(void)
{
	int	pid;

	if (!wh_typeit(&g_data.cmd[0]))
	{
		pid = fork();
		if (!pid)
		{
			signal(SIGINT, SIG_DFL);
			signal(SIGQUIT, SIG_DFL);
			is_command(&g_data.cmd[0], 0);
			exit(1);
		}
		waitpid(pid, &g_data.ret, 0);
		the_exit_code();
	}
	else
		red_in_main(&g_data.cmd[0]);
}

void	creat_child(int i)
{
	g_data.pid[i] = fork();
	if (!g_data.pid[i])
	{
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		is_command(&g_data.cmd[i], i);
		exit(1);
	}
	if (i != g_data.x)
		close(g_data.pipe[g_data.output]);
	if (i != 0)
		close(g_data.pipe[g_data.input - 2]);
	g_data.output += 2;
	g_data.input += 2;
}

void	start_exec(void)
{
	int	i;

	i = 0;
	if (g_data.x == 0)
	{
		if (!is_there_herdoc())
			for_one_command();
	}
	else
	{
		if (!is_there_herdoc())
		{
			declared_all();
			while (i < g_data.x + 1)
			{	
				pipe(&g_data.pipe[g_data.output - 1]);
				creat_child(i);
				i++;
			}
			i = -1;
			while (++i < (g_data.x + 1))
				waitpid(g_data.pid[i], &g_data.ret, 0);
			the_exit_code();
		}
	}
}
