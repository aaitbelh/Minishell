/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/19 12:39:18 by alaajili         ###   ########.fr       */
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
	while (g_data.cmds[i][j])
	{
		while (g_data.cmds[i][j] == ' ')
			j++;
		if (g_data.cmds[i][j] != ' ' && g_data.cmds[i][j] != '>' && g_data.cmds[i][j] != '<')
			g_data.word[x++] = g_data.cmds[i][j];
		j++;
	}
	g_data.word[x] = '\0';
}

// void	get_cmd(int i)
// {
// 	int	x;
// 	int	j;

// 	x = 0;
// 	j = 0;
// 	while (g_data.cmds[i][j])
// 	{
// 		while (g_data.cmds[i][j] == ' ' && x == 0)
// 			j++;
// 		if (g_data.cmds[i][j] != ' ' && g_data.cmds[i][j] != '>' && g_data.cmds[i][j] != '<')
// 			g_data.cmd[i].command[x++] = g_data.cmds[i][j];
// 		else
// 			break ;
// 		j++;
// 	}
// 	g_data.cmd[i].command[x] = '\0';
// }

// void	split_cmds(int i)
// {
// 	int	j;

// 	g_data.word_len = 0;
// 	j = 0;

// 	while (g_data.cmds[i][j])
// 	{
// 		while (g_data.cmds[i][j] == ' ' && g_data.word_len == 0)
// 			j++;
// 		if (g_data.cmds[i][j] != ' ' && g_data.cmds[i][j] != '>' && g_data.cmds[i][j] != '<')
// 			g_data.word_len++;
// 		else if (g_data.word_len != 0)
// 		{
// 			g_data.cmd[i].command = malloc(sizeof(char ) * (g_data.word_len + 1));
// 			get_cmd(i);
// 			printf("%s\n", g_data.cmd[i].command);
// 			break ;
// 		}
// 		j++;
// 	}
// 	if(g_data.cmds[i][j] == '\0')
// 	{
// 		g_data.cmd[i].command = malloc(sizeof(char ) * (g_data.word_len + 1));
// 		get_cmd(i);
// 		printf("%s\n", g_data.cmd[i].command);
// 	}
// }

void	get_cmds(int i, int j, int k)
{
	int	x;

	g_data.cmds[k] = malloc(sizeof(char ) * (i - j + 1));
	x = 0;
	while (j != i)
		g_data.cmds[k][x++] = g_data.line[j++];
	g_data.cmds[k][x] = '\0';
}

void	split_cmds(char *line, int x)
{
	int	i;
	int j;
	int	k;
	int	t[2];

	g_data.cmds = malloc(sizeof(char *) * (x + 2));
	t[0] = 1;
	t[1] = 1;
	i = 0;
	j = 0;
	k = 0;
	while (line[i])
	{
		if (line[i] == 39)
			t[0] *= -1;
		if (line[i] == 34)
			t[1] *= -1;
		if (line[i] == '|' && t[0] + t[1] == 2)
		{
			get_cmds(i, j, k);
			k++;
			j = i + 1;
		}
		if (line[i + 1] == 0)
		{
			get_cmds(i + 1, j, k);
			k++;
		}
		i++;
	}
	g_data.cmds[k] = NULL;
}

void	data_init(char *line)
{
	int	i;
	int	t[2];
	int	x;

	t[0] = 1;
	t[1] = 1;
	x = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 39)
			t[0] *= -1;
		if (line[i] == 34)
			t[1] *= -1;
		if (line[i] == '|' && t[0] + t[1] == 2)
			x++;
		i++;
	}
	if (t[0] + t[1] != 2)
		write(1, "minishell: syntax error: unclosed quote\n", 40);
	else
	{
		g_data.cmd = malloc(sizeof(t_cmd ) * (x + 1));
		split_cmds(line, x);
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	int	i;

	g_data.ev = cpy_env(env);
	g_data.sa.sa_handler = &handler;
	g_data.sb.sa_handler = SIG_IGN;
	sigaction(SIGINT, &g_data.sa, NULL);
	sigaction(SIGQUIT, &g_data.sb, NULL);
	while(1)
	{
		g_data.line = readline("minishell-$ ");
		if (!g_data.line)
			break ;
		i = 0;
		data_init(g_data.line);
	}
	return (0);
}
