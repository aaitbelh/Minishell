/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 01:09:45 by alaajili          #+#    #+#             */
/*   Updated: 2022/04/08 17:52:20 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
	g_data.t = ft_strjoin_gnl(g_data.t, tmp);
	free(tmp);
}

int	get_env_var(int i, int j, int p)
{
	int		x;
	int		r;
	char	*var;

	x = 0;
	while (ft_isalnum(g_data.cmds[i][j]) || g_data.cmds[i][j] == '_')
		j++;
	if (p == j)
	{
		g_data.t = ft_strjoin_gnl(g_data.t, "$");
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

int	handle_env_var(int i, int j)
{
	int		p;
	char	*str;

	j++;
	if (g_data.cmds[i][j] == '?')
	{
		str = ft_itoa(g_data.ret);
		g_data.t = ft_strjoin_gnl(g_data.t, str);
		free(str);
		return (j + 1);
	}
	p = j;
	j = get_env_var(i, j, p);
	return (j);
}
