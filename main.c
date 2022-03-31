/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/31 02:41:47 by alaajili         ###   ########.fr       */
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
	int	j;
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

void	init_data(int i, int k)
{
	g_data.num_of_args[i] = 0;
	g_data.num_of_files[i] = 0;
	get_num_of_args_files(i, k);
	g_data.cmd[i].arg = malloc(sizeof(char *) * (g_data.num_of_args[i] + 1));
	g_data.cmd[i].file = malloc(sizeof(t_file) * (g_data.num_of_files[i]));
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
		k = check_len(i, k);
		get_command(k, j, i);
		init_data(i, k);
		get_args_files(i, k, 0);
	}
	else
	{
		j = get_num_of_args_files_2(i, k);
		get_args_files_2(i, j, k);
	}
}

void	handle_cmds(void)
{
	int	i;

	i = 0;
	while (g_data.cmds[i])
	{
		split_cmds(i);
		i++;
	}
}

void	parse_line(char *line)
{
	int	i;
	int	t[2];

	t[0] = 1;
	t[1] = 1;
	g_data.x = 0;
	i = 0;
	while (line[i])
	{
		if (line[i] == 39 && t[1] == 1)
			t[0] *= -1;
		if (line[i] == 34 && t[0] == 1)
			t[1] *= -1;
		if (line[i] == '|' && t[0] + t[1] == 2)
			g_data.x++;
		i++;
	}
	if (t[0] + t[1] != 2)
		write(1, "minishell: syntax error: unclosed quote\n", 40);
	else
	{
		g_data.cmd = malloc(sizeof(t_cmd) * (g_data.x + 1));
		g_data.num_of_args = malloc(sizeof(int ) * (g_data.x + 1));
		g_data.num_of_files = malloc(sizeof(int ) * (g_data.x + 1));
		get_cmds(line, g_data.x);
		handle_cmds();
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	g_data.ev = cpy_env(env);
	g_data.sa.sa_handler = &handler;
	g_data.sb.sa_handler = SIG_IGN;
	sigaction(SIGINT, &g_data.sa, NULL);
	sigaction(SIGQUIT, &g_data.sb, NULL);
	while (1)
	{
		g_data.line = readline("minishell-$ ");
		if (!g_data.line)
			break ;
		parse_line(g_data.line);
		//printf("%s\n", g_data.cmd[0].command);
		for (int i=0; i < g_data.num_of_files[0]; i++)
			printf("%s=>%d\n", g_data.cmd[0].file[i].file_name, g_data.cmd[0].file[i].file_type);
		for (int i=0; g_data.cmd[0].arg[i]; i++)
			printf("%s\n", g_data.cmd[0].arg[i]);
	}
	return (0);
}
