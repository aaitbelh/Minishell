/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/01 17:49:49 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/04 02:25:12 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/minishell.h"

int	init_data(int i, int k)
{
	g_data.num_of_args[i] = 0;
	g_data.num_of_files[i] = 0;
	if (get_num_of_args_files(i, k) == 0)
		return (0);
	g_data.cmd[i].arg = malloc(sizeof(char *) * (g_data.num_of_args[i] + 1));
	g_data.cmd[i].file = malloc(sizeof(t_file) * (g_data.num_of_files[i]));
	return (1);
}

int	split_cmds(int i)
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
		if (init_data(i, k) == 0)
			return (0);
		get_args_files(i, k, 0);
	}
	else
	{
		j = get_num_of_args_files_2(i, k);
		if (!j)
			return (0);
		get_args_files_2(i, j, k);
	}
	return (1);
}

int	handle_cmds(void)
{
	int	i;

	i = 0;
	while (g_data.cmds[i])
	{
		if (split_cmds(i) == 0)
			return (0);
		i++;
	}
	return (1);
}

int	pipe_error(char *line, int i)
{
	i++;
	while (line[i] == ' ')
		i++;
	if (line[i] == '|' || line[i] == 0)
	{
		printf("minishell: syntax error near unexpected token `|'\n");
		return (0);
	}
	return (1);
}

int	parse_line(char *line)
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
		{
			if (pipe_error(line, i) == 0)
				return (0);
			g_data.x++;
		}
		i++;
	}
	if (t[0] + t[1] != 2)
	{		
		write(1, "minishell: syntax error: unclosed quote\n", 40);
		return (0);
	}
	else
	{
		g_data.cmd = malloc(sizeof(t_cmd) * (g_data.x + 1));
		g_data.num_of_args = malloc(sizeof(int ) * (g_data.x + 1));
		g_data.num_of_files = malloc(sizeof(int ) * (g_data.x + 1));
		get_cmds(line, g_data.x);
		if (handle_cmds() == 0)
			return (0);
	}
	return (1);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	g_data.ev = cpy_env(env);
	g_data.sb.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &g_data.sb, NULL);
	while(1)
	{
		g_data.sa.sa_handler = &handler;
		sigaction(SIGINT, &g_data.sa, NULL);
		g_data.line = readline("minishell-$: ");
		// g_data.line = ft_strdup("> ptr");
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
				if (parse_line(g_data.line) != 0)
					start_exec();
			}	
		}
	}
	return (0);
}
