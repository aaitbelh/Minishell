/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/21 15:16:02 by alaajili         ###   ########.fr       */
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
		if (g_data.cmds[i][j] == 39)
		{
			j++;
			while (g_data.cmds[i][j] != 39)
				g_data.cmd[i].command[x++] = g_data.cmds[i][j++];
		}
		else if (g_data.cmds[i][j] == 34)
		{
			j++;
			while (g_data.cmds[i][j] != 34)
				g_data.cmd[i].command[x++] = g_data.cmds[i][j++];
		}
		else
			g_data.cmd[i].command[x++] = g_data.cmds[i][j];
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

void	get_args_files(int i, int k)
{
	int	j;
	int	a;
	int	b;
	int	x;

	a = 0;
	b = 0;
	if (g_data.num_of_args != 0)
		g_data.cmd[i].arg = malloc(sizeof(char *) * (g_data.num_of_args + 1));
	if (g_data.num_of_files != 0)
		g_data.cmd[i].file = malloc(sizeof(t_file) * (g_data.num_of_files));
	while (g_data.cmds[i][k])
	{
		while (g_data.cmds[i][k] == ' ')
			k++;
		j = k;
		if (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<')
		{
			while (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<' && g_data.cmds[i][k] != ' ' && g_data.cmds[i][k])
				k++;
			g_data.cmd[i].arg[a] = malloc(sizeof(char ) * (k - j + 1));
			x = 0;
			while (j != k)
				g_data.cmd[i].arg[a][x++] = g_data.cmds[i][j++];
			g_data.cmd[i].arg[a][x] = 0;
			a++;
		}
		else
		{
			if (g_data.cmds[i][k] == '>')
			{
				if (g_data.cmds[i][k + 1] == '>')
				{
					g_data.cmd[i].file[b].file_type = APPOUT;
					k += 2;
				}
				else
				{
					g_data.cmd[i].file[b].file_type = OUT;
					k++;
				}
			}
			else if (g_data.cmds[i][k] == '<')
			{
				if (g_data.cmds[i][k + 1] == '<')
				{
					g_data.cmd[i].file[b].file_type = HERDOC;
					k += 2;
				}
				else
				{
					g_data.cmd[i].file[b].file_type = IN;
					k++;
				}
			}
			while (g_data.cmds[i][k] == ' ')
				k++;
			j = k;
			while (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<' && g_data.cmds[i][k] != ' ' && g_data.cmds[i][k])
				k++;
			g_data.cmd[i].file[b].file_name = malloc(sizeof(char ) * (k - j + 1));
			x = 0;
			while (j != k)
				g_data.cmd[i].file[b].file_name[x++] = g_data.cmds[i][j++];
			g_data.cmd[i].file[b].file_name[x] = 0;
			b++;
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
		{
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
		get_command(k, j, i);
		while (g_data.cmds[i][k] == ' ')
			k++;
		get_num_of_args_files(i, k);
		printf("%d\n%d\n", g_data.num_of_args, g_data.num_of_files);
		if (g_data.num_of_args != 0 || g_data.num_of_files != 0)
			get_args_files(i, k);
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
		printf("%s\n%d\n", g_data.cmd[0].file[0].file_name, g_data.cmd[0].file[0].file_type);
	}
	return (0);
}
