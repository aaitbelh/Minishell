/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/10 14:36:49 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

// void tets(void)
// {
// 	t_data
// }

void	handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}


int main(int ac , char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char *str;
	struct sigaction	sa;
	struct sigaction	sb;

	g_data.ev = cpy_env(env);
	sa.sa_handler = &handler;
	sb.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
	while(1)
	{
		str = readline("minishell$: ");
		if(!str)
			break;
	}
	return (0);
}