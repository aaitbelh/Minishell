/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/14 10:25:49 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void get_read_cmd()
{
	char *cmd_shell;
	struct sigaction	sa;
	sa.sa_handler = &handler;
	sigaction(SIGINT, &sa, NULL);
	while(1)
	{
		cmd_shell = readline("minishell$: ");
		if(!cmd_shell || !ft_strcmp(cmd_shell, "exit"))
			ft_error_fd("exit", 0);
		if(ft_strlen(cmd_shell) > 0)
			add_history(cmd_shell);
		if(is_there_space(cmd_shell))
			free(cmd_shell);
		// start_exec();
	}
}



int main(int ac , char **av, char **env)
{
	(void)ac;
	(void)av;
	struct sigaction	sb;

	g_data.ev = cpy_env(env);
	sb.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sb, NULL);
	get_read_cmd();
	return (0);
}