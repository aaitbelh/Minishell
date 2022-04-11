/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools6.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 02:57:09 by alaajili          #+#    #+#             */
/*   Updated: 2022/04/11 02:16:16 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	init_data(int i, int k)
{
	g_data.num_of_args[i] = 0;
	g_data.num_of_files[i] = 0;
	if (get_num_of_args_files(i, k) == 0)
	{
		free(g_data.cmd[i].command);
		return (0);
	}
	g_data.cmd[i].arg = malloc(sizeof(char *) * (g_data.num_of_args[i] + 1));
	g_data.cmd[i].file = malloc(sizeof(t_file) * (g_data.num_of_files[i]));
	if (!g_data.cmd[i].arg || !g_data.cmd[i].file)
		return (0);
	return (1);
}

int	split_cmds(int i)
{
	int	k;
	int	j;

	k = 0;
	j = 0;
	while (g_data.cmds[i][k] == ' ')
		k++;
	j = k;
	if (g_data.cmds[i][k] != '>' && g_data.cmds[i][k] != '<')
	{
		k = check_len(i, k);
		get_command(k, j, i);
		if (init_data(i, k) == 0)
			return (0);
		get_args_files(i, k, 0, 0);
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
