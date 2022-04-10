/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:36:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/10 21:04:45 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	single_qoutes(int i, int j)
{
	int	p;
	int	x;

	j++;
	p = j;
	x = 0;
	while (g_data.cmds[i][j] != 39)
		j++;
	g_data.t = malloc(sizeof(char ) * (j - p + 1));
	if (!g_data.t)
		return (0);
	while (p != j)
		g_data.t[x++] = g_data.cmds[i][p++];
	g_data.t[x] = 0;
	return (j + 1);
}

char	*cpy_tmp(int i, int j, int p, char *tmp)
{
	int		x;

	x = 0;
	while (p != j)
		tmp[x++] = g_data.cmds[i][p++];
	tmp[x] = 0;
	return (tmp);
}

int	double_qoutes(int i, int j)
{
	int		p;
	char	*tmp;

	g_data.t = ft_strdup("");
	j++;
	while (g_data.cmds[i][j] != 34)
	{
		p = j;
		while (g_data.cmds[i][j] != '$' && g_data.cmds[i][j] != 34)
			j++;
		tmp = malloc(sizeof(char ) * (j - p + 1));
		if (!tmp)
			return (0);
		tmp = cpy_tmp(i, j, p, tmp);
		g_data.t = ft_strjoin_gnl(g_data.t, tmp);
		free(tmp);
		if (g_data.cmds[i][j] == '$')
			j = handle_env_var(i, j);
	}
	return (j + 1);
}

int	without_qoutes(int i, int j, int k)
{
	int		p;
	char	*tmp;

	g_data.t = ft_strdup("");
	while (g_data.cmds[i][j] != 34 && g_data.cmds[i][j] != 39 && j != k)
	{
		p = j;
		while (g_data.cmds[i][j] != '$' && g_data.cmds[i][j] != 34
			&& g_data.cmds[i][j] != 39 && j < k)
			j++;
		tmp = malloc(sizeof(char ) * (j - p + 1));
		if (!tmp)
			return (0);
		tmp = cpy_tmp(i, j, p, tmp);
		g_data.t = ft_strjoin_gnl(g_data.t, tmp);
		free(tmp);
		if (g_data.cmds[i][j] == '$')
		{
			if (g_data.cmds[i][j + 1] != 34 && g_data.cmds[i][j + 1] != 39)
				j = handle_env_var(i, j);
			else
				j++;
		}
	}
	return (j);
}

void	get_command(int k, int j, int i)
{
	g_data.cmd[i].command = ft_strdup("");
	while (j != k)
	{
		if (g_data.cmds[i][j] == 39)
		{
			j = single_qoutes(i, j);
			g_data.cmd[i].command
				= ft_strjoin_gnl(g_data.cmd[i].command, g_data.t);
			free(g_data.t);
		}
		else if (g_data.cmds[i][j] == 34)
		{
			j = double_qoutes(i, j);
			g_data.cmd[i].command
				= ft_strjoin_gnl(g_data.cmd[i].command, g_data.t);
			free(g_data.t);
		}
		else
		{
			j = without_qoutes(i, j, k);
			g_data.cmd[i].command
				= ft_strjoin_gnl(g_data.cmd[i].command, g_data.t);
			free(g_data.t);
		}
	}
}
