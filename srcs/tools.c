/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:36:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/31 12:47:59 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**cpy_env(char **str)
{
	char	**table;
	int		i;
	int		j;

	i = 0;
	while (str[i])
		i++;
	table = malloc(sizeof(char *) * i);
	if (!table)
		return (NULL);
	i = 0;
	while (str[i])
	{
		j = 0;
		table[i] = malloc(sizeof(char ) * strlen(str[i]));
		while (str[i][j])
		{
			table[i][j] = str[i][j];
			j++;
		}
		i++;
	}
	return (table);
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
