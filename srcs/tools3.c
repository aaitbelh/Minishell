/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:27:01 by alaajili          #+#    #+#             */
/*   Updated: 2022/03/31 01:25:15 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cpy_arg(int i, int k, int j, int a)
{
	int	x;

	x = 0;
	g_data.cmd[i].arg[a] = malloc(sizeof(char ) * (k - j + 1));
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
}

void	cpy_file_name(int i, int k, int j, int b)
{
	int	x;

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
}

int	get_file_type(int i, int k, int b)
{
	if (g_data.cmds[i][k] == '>')
	{
		if (g_data.cmds[i][k + 1] == '>')
		{
			g_data.cmd[i].file[b].file_type = APPOUT;
			k++;
		}
		else
			g_data.cmd[i].file[b].file_type = OUT;
		k++;
	}
	else if (g_data.cmds[i][k] == '<')
	{
		if (g_data.cmds[i][k + 1] == '<')
		{
			g_data.cmd[i].file[b].file_type = HERDOC;
			k++;
		}
		else
			g_data.cmd[i].file[b].file_type = IN;
		k++;
	}
	return (k);
}

int	check_len(int i, int k)
{
	while (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<'
		&& g_data.cmds[i][k] != ' ' && g_data.cmds[i][k])
	{
		k = skip_quotes(i, k);
		k++;
	}
	return (k);
}

void	get_args_files(int i, int k, int b)
{
	int	j;
	int	a;

	a = 0;
	while (g_data.cmds[i][k])
	{
		while (g_data.cmds[i][k] == ' ')
			k++;
		j = k;
		if (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<'
			&& g_data.cmds[i][k])
		{
			k = check_len(i, k);
			cpy_arg(i, k, j, a);
			a++;
		}
		else if (g_data.cmds[i][k])
		{
			k = get_file_type(i, k, b);
			while (g_data.cmds[i][k] == ' ')
				k++;
			j = k;
			k = check_len(i, k);
			cpy_file_name(i, k, j, b);
			b++;
		}
	}
	g_data.cmd[i].arg[a] = NULL;
}
