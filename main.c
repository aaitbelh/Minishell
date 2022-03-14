/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/14 21:21:29 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

void	handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	cpy_word(int i)
{
	int x;
	int	j;

	x = 0;
	j = 0;
	g_data.word = malloc(sizeof(char ) * (g_data.word_len + 1));
	while (g_data.cmds[i][j] && g_data.cmds[i][j] != '>' && g_data.cmds[i][j] != '<')
	{
		if (g_data.cmds[i][j] != ' ')
			g_data.word[x++] = g_data.cmds[i][j];
		j++;
	}
	g_data.word[x] = '\0';
}



void	split_cmds(int i)
{
	int	j;

	g_data.word_len = 0;
	j = 0;
	while (g_data.cmds[i][j])
	{
		if (g_data.cmds[i][j] != ' ')
			g_data.word_len++;
		if (g_data.cmds[i][j + 1] == '<' || g_data.cmds[i][j + 1] == '>')
		{
			cpy_word(i);
			g_data.cmd[i].command = strdup(g_data.word);
		}
		j++;
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	char				*str;
	struct sigaction	sa;
	struct sigaction	sb;

	g_data.ev = cpy_env(env);
	sa.sa_handler = &handler;
	sb.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sb, NULL);
	while(1)
	{
		str = readline("minishell-$ ");
		if(!str)
			break ;
		int x = 0;
		for (int i = 0; str[i]; i++){
			if (str[i] == '|')
				x++;
		}
		g_data.cmd = malloc(sizeof(t_cmd ) * (x + 1));
		g_data.cmds = ft_split(str, '|');
		for(int i = 0; g_data.cmds[i]; i++)
			split_cmds(i);
	}
	return (0);
}
