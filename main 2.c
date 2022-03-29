/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main 2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/26 16:10:41 by aaitbelh         ###   ########.fr       */
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
		WH_typeit(cmd_shell);
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