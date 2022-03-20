/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/20 17:20:39 by alaajili         ###   ########.fr       */
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

void	cpy_cmds(int i, int j, int k)
{
	int	x;

	g_data.cmds[k] = malloc(sizeof(char ) * (i - j + 1));
	x = 0;
	while (j != i)
		g_data.cmds[k][x++] = g_data.line[j++];
	g_data.cmds[k][x] = '\0';
}

void	get_cmds(char *line, int x)
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
			cpy_cmds(i, j, k);
			k++;
			j = i + 1;
		}
		if (line[i + 1] == 0)
		{
			cpy_cmds(i + 1, j, k);
			k++;
		}
		i++;
	}
	g_data.cmds[k] = NULL;
}

void	get_command(int k, int j, int i)
{
	int	x;

	g_data.cmd[i].command = malloc(sizeof(char ) * (k - j + 1));
	x = 0;
	while (j != k)
	{
		g_data.cmd[i].command[x] = g_data.cmds[i][j];
		x++;
		j++;
	}
	g_data.cmd[i].command[x] = 0;
}

void	get_num_of_args_files(int i, int k)
{
	g_data.num_of_args = 0;
	g_data.num_of_files = 0;
	while (g_data.cmds[i][k])
	{
		while (g_data.cmds[i][k] == ' ')
			k++;
		if (g_data.cmds[i][k] == '>' || g_data.cmds[i][k] == '<')
		{
			g_data.num_of_files++;
			if (g_data.cmds[i][k] == '>' && g_data.cmds[i][k + 1] == '<')
			{
				write(1, "minishell: syntax error near unexpected token `<'\n", 50);
				g_data.num_of_args = 0;
				g_data.num_of_files = 0;
				return ;
			}
			if (g_data.cmds[i][k] == '<' && g_data.cmds[i][k + 1] == '>')
			{
				write(1, "minishell: syntax error near unexpected token `>'\n", 50);
				g_data.num_of_args = 0;
				g_data.num_of_files = 0;
				return ;
			}
			if (g_data.cmds[i][k + 1] == '>' || g_data.cmds[i][k + 1] == '<')
				k += 2;
			else
				k++;
			while (g_data.cmds[i][k] == ' ')
				k++;
			if (g_data.cmds[i][k] == '>')
			{
				write(1, "minishell: syntax error near unexpected token `>'\n", 50);
				g_data.num_of_args = 0;
				g_data.num_of_files = 0;
				return ;
			}
			if (g_data.cmds[i][k] == '<')
			{
				write(1, "minishell: syntax error near unexpected token `<'\n", 50);
				g_data.num_of_args = 0;
				g_data.num_of_files = 0;
				return ;
			}
		}
		else if (g_data.cmds[i][k])
			g_data.num_of_args++;
		//k++;
		while (g_data.cmds[i][k] == ' ')
			k++;
		while (g_data.cmds[i][k] != ' ' && g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<')
		{
			if (!g_data.cmds[i][k])
				break ;
			if (g_data.cmds[i][k] == 34)
			{
				k++;
				while (g_data.cmds[i][k] != 34)
					k++;
			}
			else if (g_data.cmds[i][k] == 39)
			{
				k++;
				while (g_data.cmds[i][k] != 39)
					k++;
			}
			k++;
		}
	}
}

void	split_cmds(int i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (g_data.cmds[i][k] == ' ')
	{
		k++;
		j++;
	}
	if (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<')
	{
		while (g_data.cmds[i][k] && g_data.cmds[i][k] != '>' &&
			g_data.cmds[i][k] != '<' && g_data.cmds[i][k] != ' ')
			k++;
		get_command(k, j, i);
		while (g_data.cmds[i][k] == ' ')
			k++;
		get_num_of_args_files(i, k);
		printf("%d\n%d\n", g_data.num_of_args, g_data.num_of_files);
		//get_args_files(i, k);
	}
}

void	handle_cmds(void)
{
	int i;

	i = 0;
	while (g_data.cmds[i])
	{
		split_cmds(i);
		i++;
	}
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
		if (line[i] == 39 && t[1] == 1)
			t[0] *= -1;
		if (line[i] == 34 && t[0] == 1)
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
		get_cmds(line, x);
		handle_cmds();
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
