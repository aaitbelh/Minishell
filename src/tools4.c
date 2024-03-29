/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 00:59:44 by alaajili          #+#    #+#             */
/*   Updated: 2022/04/10 21:08:46 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	get_num_of_files(int i, int k)
{
	while (g_data.cmds[i][k])
	{	
		while (g_data.cmds[i][k] == ' ')
			k++;
		if (g_data.cmds[i][k] == '<' || g_data.cmds[i][k] == '>')
		{
			g_data.num_of_files[i]++;
			if (check_error(i, k) == 0)
				return (0);
			if (g_data.cmds[i][k + 1] == '>' || g_data.cmds[i][k + 1] == '<')
				k += 2;
			else
				k++;
			while (g_data.cmds[i][k] == ' ')
				k++;
			if (check_error_2(i, k) == 0)
				return (0);
			k = check_len(i, k);
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
	g_data.num_of_files[i] = 0;
	k = get_num_of_files(i, k);
	if (!k)
		return (0);
	j = k;
	k = check_len(i, k);
	get_command(k, j, i);
	if (k == j)
	{
		free(g_data.cmd[i].command);
		g_data.cmd[i].command = NULL;
	}
	while (g_data.cmds[i][k] == ' ')
		k++;
	if (get_num_of_args_files(i, k) == 0)
	{
		free(g_data.cmd[i].command);
		return (0);
	}
	return (j);
}

void	get_args_files_2(int i, int j, int k)
{
	int	b;
	int	h;

	g_data.cmd[i].arg = malloc(sizeof(char *) * (g_data.num_of_args[i] + 1));
	g_data.cmd[i].file = malloc(sizeof(t_file) * (g_data.num_of_files[i]));
	if (!g_data.cmd[i].arg || !g_data.cmd[i].file)
		return ;
	b = 0;
	while (k != j)
	{	
		k = get_file_type(i, k, b);
		while (g_data.cmds[i][k] == ' ')
			k++;
		h = k;
		k = check_len(i, k);
		cpy_file_name(i, k, h, b);
		b++;
		while (g_data.cmds[i][k] == ' ')
			k++;
	}
	while (g_data.cmds[i][k] != ' ' && g_data.cmds[i][k] != '>'
		&& g_data.cmds[i][k] != '<' && g_data.cmds[i][k])
		k++;
	get_args_files(i, k, 0, b);
}
