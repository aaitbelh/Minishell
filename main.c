/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/22 15:51:30 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


void get_read_cmd()
{
	char *cmd_shell;
	struct sigaction	sa;
	char **test;
	sa.sa_handler = &handler;
	sigaction(SIGINT, &sa, NULL);
	while(1)
	{
		cmd_shell = readline("minishell$: ");
		if(!cmd_shell || !ft_strcmp(cmd_shell, "exit"))
			ft_error_ex("exit", 0);
		if(ft_strlen(cmd_shell) > 0)
			add_history(cmd_shell);
		// if(is_there_space(cmd_shell))
		// 	free(cmd_shell);
		if(!ft_strncmp(cmd_shell, "cd", 2))
		{
			test = ft_split(cmd_shell, ' ');
			ft_cd(test);
		}
		if(!strcmp(cmd_shell, "pwd"))
		{
			ft_pwd();
		}
		if(!ft_strncmp(cmd_shell, "echo", 4))
		{
			test = ft_split(cmd_shell, ' ');
			ft_echo(&test[1]);
		}
		if(!ft_strcmp(cmd_shell, "env"))
		{
			int i;
			i = 0;
			while(g_data.ev[i])
			{
				if(strchr(g_data.ev[i], '='))
					printf("%s\n", g_data.ev[i]);
				i++;
			}
		}
		if(!strncmp(cmd_shell, "export", 6))
		{
			test = ft_split(cmd_shell, ' ');
			ft_export(test);
		}
		if(!strncmp(cmd_shell, "unset", 5))
		{
			test = ft_split(cmd_shell, ' ');
			unset(test);
		}
		else
		{
			int i = 0;
			int l = 1;
			int pid;
			g_data.n = 1;
			g_data.input = -2;
			g_data.output = 1;
			g_data.cmd = malloc(sizeof(t_cmd) * g_data.n);
			g_data.pipe = malloc(sizeof(int) * g_data.n - 1);
			g_data.cmd->command = ft_strdup("ls");
			g_data.cmd->arg = malloc(sizeof(char *) * 2);
			g_data.cmd->arg[0] = ft_strdup("-la");
			g_data.cmd->arg[1] = NULL;
			g_data.cmd[i].file = NULL;
			while(i < l)
			{
				pipe(&g_data.pipe[g_data.output - 1]);
				pid = fork();
				if(!pid)
					is_command();
				i++;
			}
			i = 0;
			while(i < l)
			{
				waitpid(-1, NULL, 0);
				i++;
			}
		}
		free(cmd_shell);
	}
}



int main(int ac , char **av, char **env)
{
	(void)ac;
	(void)av;
	struct sigaction	sb;

	g_data.ev = cpy_env(env);
	g_data.exp = cpy_exp(g_data.ev);
	sb.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sb, NULL);
	get_read_cmd();
	return (0);
}