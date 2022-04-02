/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:36:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/02 18:12:16 by alaajili         ###   ########.fr       */
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
	while (p != j)
		g_data.t[x++] = g_data.cmds[i][p++];
	g_data.t[x] = 0;
	return (j + 1);
}

int	is_in_env(char *var)
{
	int		i;
	int		j;
	char	*tmp;

	i = 0;
	while (g_data.ev[i])
	{
		j = 0;
		while (g_data.ev[i][j] != '=')
			j++;
		tmp = malloc(sizeof(char ) * (j + 1));
		j = -1;
		while (g_data.ev[i][++j] != '=')
			tmp[j] = g_data.ev[i][j];
		tmp[j] = 0;
		if (!ft_strncmp(tmp, var, ft_strlen(tmp)))
		{
			free(tmp);
			return (i);
		}
		free(tmp);
		i++;
	}
	return (-1);
}

void	cpy_paste(int r)
{
	int		i;
	int		j;
	int		x;
	char	*tmp;

	x = 0;
	i = 0;
	while (g_data.ev[r][i] != '=')
		i++;
	i++;
	j = i;
	while (g_data.ev[r][i])
		i++;
	tmp = malloc(sizeof(char ) * (i - j + 1));
	while (j != i)
		tmp[x++] = g_data.ev[r][j++];
	tmp[x] = 0;
	g_data.t = ft_strjoin(g_data.t, tmp);
	free(tmp);
}

int	handle_env_var(int i, int j)
{
	int		p;
	int		x;
	int		r;
	char	*var;

	j++;
	p = j;
	x = 0;
	while(ft_isalnum(g_data.cmds[i][j]) || g_data.cmds[i][j] == '_')
		j++;
	if (p == j)
	{
		g_data.t = ft_strjoin(g_data.t, "$");
		return (j);
	}
	var = malloc(sizeof(char ) * (j - p + 1));
	while (p != j)
		var[x++] = g_data.cmds[i][p++];
	var[x] = 0;
	r = is_in_env(var);
	free(var);
	if (r != -1)
		cpy_paste(r);
	return (j);
}

int	double_qoutes(int i, int j)
{
	int	p;
	int	x;
	char	*tmp;

	g_data.t = ft_strdup("");
	j++;
	while (g_data.cmds[i][j] != 34)
	{
		p = j;
		while (g_data.cmds[i][j] != '$' && g_data.cmds[i][j] != 34)
			j++;
		tmp = malloc(sizeof(char ) * (j - p + 1));
		x = 0;
		while (p != j)
			tmp[x++] = g_data.cmds[i][p++];
		tmp[x] = 0;
		g_data.t = ft_strjoin(g_data.t, tmp);
		free(tmp);
		if (g_data.cmds[i][j] == '$')
			j = handle_env_var(i, j);
	}
	return (j + 1);
}

int	without_qoutes(int i, int j, int k)
{
	int	p;
	int	x;
	char	*tmp;

	g_data.t = ft_strdup("");
	while (g_data.cmds[i][j] != 34 && g_data.cmds[i][j] != 39 && j != k)
	{
		p = j;
		while (g_data.cmds[i][j] != '$' && g_data.cmds[i][j] != 34
			&& g_data.cmds[i][j] != 39 && j < k)
			j++;
		tmp = malloc(sizeof(char ) * (j - p + 1));
		x = 0;
		while (p != j)
			tmp[x++] = g_data.cmds[i][p++];
		tmp[x] = 0;
		g_data.t = ft_strjoin(g_data.t, tmp);
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
			g_data.cmd[i].command = ft_strjoin(g_data.cmd[i].command, g_data.t);
			free(g_data.t);
		}
		else if (g_data.cmds[i][j] == 34)
		{
			j = double_qoutes(i, j);
			g_data.cmd[i].command = ft_strjoin(g_data.cmd[i].command, g_data.t);
			free(g_data.t);
		}
		else
		{
			j = without_qoutes(i, j, k);
			g_data.cmd[i].command = ft_strjoin(g_data.cmd[i].command, g_data.t);
			free(g_data.t);
		}
	}
}
