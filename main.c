/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/25 17:54:13 by aaitbelh         ###   ########.fr       */
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
		else if(!strcmp(cmd_shell, "pwd"))
		{
			ft_pwd();
		}
		else if(!ft_strncmp(cmd_shell, "echo", 4))
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
			// test = ft_split(cmd_shell, ' ');
			int i = 0;
			int l = 1;
			int pid;
			g_data.n = 0;
			g_data.input = 0;
			g_data.output = 1;
			g_data.number_cmd = 2;
			g_data.number_file = 2;
			g_data.cmd = malloc(sizeof(t_cmd) * 2);
			g_data.cmd[0].file = malloc(sizeof(t_file) * 2);
			g_data.cmd[1].file = malloc(sizeof(t_file) * 2);
			g_data.cmd[0].file[0].file_type = 3;
			g_data.cmd[0].file[0].file_name = ft_strdup("stp");	
			g_data.cmd[0].file[1].file_type = 3;
			g_data.cmd[0].file[1].file_name = ft_strdup("stp_2");	
			g_data.cmd[1].file[0].file_type = 3;
			g_data.cmd[1].file[0].file_name = ft_strdup("stop");	
			g_data.cmd[1].file[1].file_type = 3;
			g_data.cmd[1].file[1].file_name = ft_strdup("stop_oo");	
			// g_data.cmd[0].file->file_name = ft_strdup("file");
			// g_data.cmd[0].file->file_type = 1;
			// g_data.cmd->arg[0] = ft_strdup("-la");
			//g_data.cmd->arg = NULL;
			if(is_there_herdoc())
			{
				printf("you press C^");
				exit(1);
			}
			char buf[1000];
			 int y = read(g_data.cmd[0].p_herdoc, buf, 1000);
			 buf[y] = '\0';
			printf(" ------------ %s\n", buf);
			y = read(g_data.cmd[1].p_herdoc, buf, 1000);
			 buf[y] = '\0';
			printf("----------- %s\n", buf);
			exit(0);
			while(i < l)
			{
				// printf("%d\n", g_data.n);
				pipe(&g_data.pipe[g_data.output - 1]);
				pid = fork();
				if(!pid)
					is_command(&g_data.cmd[i], i);
				g_data.n++;
				g_data.output += 2;
				g_data.input += 2;
				i++;
			}
			i = 0;
			while(i < g_data.number_cmd * 2)
			{
				close(g_data.pipe[i]);
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