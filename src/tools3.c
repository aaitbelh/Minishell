/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 16:27:01 by alaajili          #+#    #+#             */
/*   Updated: 2022/04/07 02:12:01 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	cpy_arg(int i, int k, int j, int a)
{
	g_data.cmd[i].arg[a] = ft_strdup("");
	while (j != k)
	{
		if (g_data.cmds[i][j] == 39)
		{
			j = single_qoutes(i, j);
			g_data.cmd[i].arg[a]
				= ft_strjoin_gnl(g_data.cmd[i].arg[a], g_data.t);
			free(g_data.t);
		}
		else if (g_data.cmds[i][j] == 34)
		{
			j = double_qoutes(i, j);
			g_data.cmd[i].arg[a]
				= ft_strjoin_gnl(g_data.cmd[i].arg[a], g_data.t);
			free(g_data.t);
		}
		else
		{
			j = without_qoutes(i, j, k);
			g_data.cmd[i].arg[a]
				= ft_strjoin_gnl(g_data.cmd[i].arg[a], g_data.t);
			free(g_data.t);
		}
	}
}

void	cpy_file_name(int i, int k, int j, int b)
{
	g_data.cmd[i].file[b].file_name = ft_strdup("");
	while (j != k)
	{
		if (g_data.cmds[i][j] == 39)
		{
			j = single_qoutes(i, j);
			g_data.cmd[i].file[b].file_name
				= ft_strjoin_gnl(g_data.cmd[i].file[b].file_name, g_data.t);
			free(g_data.t);
		}
		else if (g_data.cmds[i][j] == 34)
		{
			j = double_qoutes(i, j);
			g_data.cmd[i].file[b].file_name
				= ft_strjoin_gnl(g_data.cmd[i].file[b].file_name, g_data.t);
			free(g_data.t);
		}
		else
		{
			j = without_qoutes(i, j, k);
			g_data.cmd[i].file[b].file_name
				= ft_strjoin_gnl(g_data.cmd[i].file[b].file_name, g_data.t);
			free(g_data.t);
		}
	}
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
	while (g_data.cmds[i][k] == ' ')
		k++;
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

void	get_args_files(int i, int k, int a, int b)
{
	int	j;

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
			j = k;
			k = check_len(i, k);
			cpy_file_name(i, k, j, b);
			b++;
		}
	}
	g_data.cmd[i].arg[a] = NULL;
}
