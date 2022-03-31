/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/31 22:44:50 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"


void is_builtins(t_cmd *cmd)
{
	int	i;

	i = 0;
	if(!strcmp("cd", cmd->command))
		ft_cd(cmd->arg[0]);
	else if(!strcmp("pwd", cmd->command))
		ft_pwd();
	else if(!strcmp("echo", cmd->command))
		ft_echo(cmd->arg);
	else if (!strcmp("export", cmd->command))
		ft_export(cmd->arg);
	else if (!strcmp("unset", cmd->command))
		unset(cmd->arg);
	else if (!strcmp("exit", cmd->command))
		ft_exit(cmd);
	else if(!strcmp("env", cmd->command))
	{
		while(g_data.ev[i])
		{
			if(strchr(g_data.ev[i], '='))
				printf("%s\n", g_data.ev[i]);
			i++;
		}
	}
}

void red_in_main(t_cmd *cmd)
{

	g_data.out = dup(1);
	g_data.in = dup(0);
	red_files(cmd, 0);	
}

int	wh_typeit(t_cmd *cmd)
{
	if(!strcmp(cmd->command, "cd") || !strcmp(cmd->command, "pwd") || !strcmp(cmd->command, "echo") || !strcmp(cmd->command, "export") || !strcmp(cmd->command, "unset") ||!strcmp(cmd->command, "exit") || !strcmp(cmd->command, "env"))
		return (1);
	return (0);
}

void start_exec()
{
	int i;
	i = 0;
	int pid;
	int ret;
	g_data.output = 1;
	g_data.input = 0;
	if(g_data.x == 0)
	{
		if(!is_there_herdoc())
		{
			if (!wh_typeit(&g_data.cmd[i]))
			{
				pid = fork();
				if(!pid)
				{
					signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
					is_command(&g_data.cmd[i], 0);
					exit(1);
				}
				ret = waitpid(pid, NULL, 0);
			}
			else
			{
				if(g_data.num_of_files[0] != 0)
					red_in_main(&g_data.cmd[0]);
				is_builtins(&g_data.cmd[i]);
				dup2(g_data.out, 1);
				dup2(g_data.in, 0);
			}
		}
	}
	else
	{
		g_data.pipe = malloc(sizeof(int) * g_data.x * 2);
		if(!is_there_herdoc())
		{
			while(i < g_data.x + 1)
			{	
					pipe(&g_data.pipe[g_data.output - 1]);
					pid = fork();
					if(!pid)
					{
						signal(SIGINT, SIG_DFL);
						signal(SIGQUIT, SIG_DFL);
						is_command(&g_data.cmd[i],i);
						exit(1);
					}
					if(i != g_data.x)
						close(g_data.pipe[g_data.output]);
					if(i != 0)
						close(g_data.pipe[g_data.input - 2]);
					g_data.output += 2;
					g_data.input += 2;
					i++;
			}
			i = -1;
			while(++i < (g_data.x + 1))
				waitpid(-1,  NULL, 0);	
		}
	}
}

void	handler_2(int sig)
{
	(void)sig;
	write(1, "\n", 1);
}

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
	while (g_data.cmds[i][k])
	{
		while (g_data.cmds[i][k] == ' ')
			k++;
		if (g_data.cmds[i][k] == '>' || g_data.cmds[i][k] == '<')
		{
			g_data.num_of_files[i]++;
			if (g_data.cmds[i][k] == '>' && g_data.cmds[i][k + 1] == '<')
			{
				write(1, "minishell: syntax error near unexpected token `<'\n", 50);
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
				return ;
			}
			if (g_data.cmds[i][k] == '<' && g_data.cmds[i][k + 1] == '>')
			{
				write(1, "minishell: syntax error near unexpected token `>'\n", 50);
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
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
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
				return ;
			}
			if (g_data.cmds[i][k] == '<')
			{
				write(1, "minishell: syntax error near unexpected token `<'\n", 50);
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
				return ;
			}
		}
		else if (g_data.cmds[i][k])
			g_data.num_of_args[i]++;
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

void	get_args_files(int i, int k, int b)
{
	int	j;
	int	a;
	int	x;

	a = 0;
	while (g_data.cmds[i][k])
	{
		while (g_data.cmds[i][k] == ' ')
			k++;
		j = k;
		if (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<' && g_data.cmds[i][k])
		{
			while (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<' && g_data.cmds[i][k] != ' ' && g_data.cmds[i][k])
			{
				if (g_data.cmds[i][k] == 39)
				{
					k++;
					while(g_data.cmds[i][k] != 39)
						k++;
				}
				else if (g_data.cmds[i][k] == 34)
				{
					k++;
					while (g_data.cmds[i][k] != 34)
						k++;
				}
				k++;
			}
			g_data.cmd[i].arg[a] = malloc(sizeof(char ) * (k - j + 1));
			x = 0;
			while (j != k)
			{
				if (g_data.cmds[i][j] == 39)
				{
					j++;
					while (g_data.cmds[i][j] != 39)
						g_data.cmd[i].arg[a][x++] = g_data.cmds[i][j++];
				}
				else if (g_data.cmds[i][j] == 34)
				{
					j++;
					while (g_data.cmds[i][j] != 34)
						g_data.cmd[i].arg[a][x++] = g_data.cmds[i][j++];
				}
				else
					g_data.cmd[i].arg[a][x++] = g_data.cmds[i][j];
				j++;
			}
			g_data.cmd[i].arg[a][x] = 0;
			a++;
		}
		else if (g_data.cmds[i][k])
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
			{
				if (g_data.cmds[i][k] == 39)
				{
					k++;
					while(g_data.cmds[i][k] != 39)
						k++;
				}
				else if (g_data.cmds[i][k] == 34)
				{
					k++;
					while (g_data.cmds[i][k] != 34)
						k++;
				}
				k++;
			}
			g_data.cmd[i].file[b].file_name = malloc(sizeof(char ) * (k - j + 1));
			x = 0;
			while (j != k)
			{
				if (g_data.cmds[i][j] == 39)
				{
					j++;
					while (g_data.cmds[i][j] != 39)
						g_data.cmd[i].file[b].file_name[x++] = g_data.cmds[i][j++];
				}
				else if (g_data.cmds[i][j] == 34)
				{
					j++;
					while (g_data.cmds[i][j] != 34)
						g_data.cmd[i].file[b].file_name[x++] = g_data.cmds[i][j++];
				}
				else
					g_data.cmd[i].file[b].file_name[x++] = g_data.cmds[i][j];
				j++;
			}
			g_data.cmd[i].file[b].file_name[x] = 0;
			b++;
		}
	}
	g_data.cmd[i].arg[a] = NULL;
}

int	get_num_of_files(int i, int k)
{
	while (g_data.cmds[i][k])
	{
		
		while (g_data.cmds[i][k] == ' ')
			k++;
		if (g_data.cmds[i][k] == '<' || g_data.cmds[i][k] == '>')
		{
			g_data.num_of_files[i]++;
			if (g_data.cmds[i][k] == '>' && g_data.cmds[i][k + 1] == '<')
			{
				write(1, "minishell: syntax error near unexpected token `<'\n", 50);
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
				return (0);
			}
			if (g_data.cmds[i][k] == '<' && g_data.cmds[i][k + 1] == '>')
			{
				write(1, "minishell: syntax error near unexpected token `>'\n", 50);
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
				return (0);
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
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
				return (0);
			}
			if (g_data.cmds[i][k] == '<')
			{
				write(1, "minishell: syntax error near unexpected token `<'\n", 50);
				g_data.num_of_args[i] = 0;
				g_data.num_of_files[i] = 0;
				return (0);
			}
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
		else
			return (k);
	}
	return (k);
}

int	get_num_of_args_files_2(int i, int k)
{
	int	j;
	g_data.num_of_args[i] = 0;
	g_data.num_of_files[i] =  0;

	k = get_num_of_files(i, k);
	//printf("%d\n", k);
	if (!k)
		return (0);
	j = k;
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
	//printf("%d\n%d\n", g_data.num_of_args[i], g_data.num_of_files[i]);
	return (j);
}

void	get_args_files_2(int i, int j, int k)
{
	int	a;
	int	b;
	int	h;
	int x;

	g_data.cmd[i].arg = malloc(sizeof(char *) * (g_data.num_of_args[i] + 1));
	g_data.cmd[i].file = malloc(sizeof(t_file) * (g_data.num_of_files[i]));
	a = 0;
	b = 0;
	while(k != j)
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
		h = k;
		while (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<' && g_data.cmds[i][k] != ' ' && g_data.cmds[i][k])
		{
			if (g_data.cmds[i][k] == 39)
			{
				k++;
				while(g_data.cmds[i][k] != 39)
					k++;
			}
			else if (g_data.cmds[i][k] == 34)
			{
				k++;
				while (g_data.cmds[i][k] != 34)
					k++;
			}
			k++;
		}
		g_data.cmd[i].file[b].file_name = malloc(sizeof(char ) * (k - h + 1));
		x = 0;
		while (h != k && g_data.cmds[i][h])
		{
			if (g_data.cmds[i][h] == 39)
			{
				h++;
				while (g_data.cmds[i][h] != 39)
					g_data.cmd[i].file[b].file_name[x++] = g_data.cmds[i][h++];
			}
			else if (g_data.cmds[i][h] == 34)
			{
				h++;
				while (g_data.cmds[i][h] != 34)
					g_data.cmd[i].file[b].file_name[x++] = g_data.cmds[i][h++];
			}
			else
				g_data.cmd[i].file[b].file_name[x++] = g_data.cmds[i][h];
			h++;
		}
		g_data.cmd[i].file[b].file_name[x] = 0;
		b++;
		while (g_data.cmds[i][k] == ' ')
			k++;
	}
	while (g_data.cmds[i][k] != ' ' && g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<' && g_data.cmds[i][k])
		k++;
	get_args_files(i, k, b);
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
		g_data.num_of_args[i] = 0;
		g_data.num_of_files[i] = 0;
		get_num_of_args_files(i, k);
		g_data.cmd[i].arg = malloc(sizeof(char *) * (g_data.num_of_args[i] + 1));
		g_data.cmd[i].file = malloc(sizeof(t_file) * (g_data.num_of_files[i]));
		get_args_files(i, k, 0);
	}
	else
	{
		j = get_num_of_args_files_2(i, k);
		//printf("%d\n", j);
		get_args_files_2(i, j, k);
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
		g_data.cmd = malloc(sizeof(t_cmd ) * (g_data.x + 1));
		g_data.num_of_args = malloc(sizeof(int ) * (g_data.x + 1));
		g_data.num_of_files = malloc(sizeof(int ) * (g_data.x + 1));
		get_cmds(line, g_data.x);
		handle_cmds();
	}
}

int main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;

	g_data.ev = cpy_env(env);
	g_data.exp = cpy_exp(g_data.ev);
	sigaction(SIGQUIT, &g_data.sb, NULL);
	g_data.sb.sa_handler = SIG_IGN;
	g_data.sa.sa_flags = SA_RESTART;
	g_data.sb.sa_flags = SA_RESTART;
	while(1)
	{
		g_data.sa.sa_handler = &handler;
		sigaction(SIGINT, &g_data.sa, NULL);
		g_data.line = readline("minishell$: ");
		g_data.sa.sa_handler = &handler_2;
		sigaction(SIGINT, &g_data.sa, NULL);
		if (!g_data.line)
			break ;
		if(ft_strlen(g_data.line) > 0)
			add_history(g_data.line);
		if(g_data.line[0] != '\0')
		{	
			if(!is_there_space(g_data.line))
			{
				data_init(g_data.line);
				start_exec();
			}	
		}
	}
	return (0);
}
