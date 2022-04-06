/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools0.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 12:46:48 by alaajili          #+#    #+#             */
/*   Updated: 2022/04/06 18:01:59 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	join_th_errors_re(char *s1, char *s2, char *s3, int ret)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(s1, s2);
	new = ft_strjoin(tmp, s3);
	free(tmp);
	ft_putendl_fd(new, 2);
	free(new);
	g_data.ret = ret;
	return (ret);
}

void	print_the_exp(void)
{
	int	i;

	i = 0;
	twodfree(g_data.exp);
	g_data.exp = cpy_exp(g_data.ev);
	while (g_data.exp[i])
	{
		printf("declare -x %s\n", g_data.exp[i]);
		i++;
	}
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
	int	j;
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
