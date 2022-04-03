/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:42:20 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/01 00:04:22 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**delete_it(int ind)
{
	int		i;
	int		j;
	char	**new_table;

	j = 0;
	i = 0;
	while (g_data.ev[i])
		i++;
	new_table = malloc(sizeof(char *) * i);
	i = 0;
	while (g_data.ev[i])
	{
		if (ind != i)
		{
			new_table[j] = ft_strdup(g_data.ev[i]);
			j++;
		}
		i++;
	}
	twodfree(g_data.ev);
	new_table[j] = NULL;
	return (new_table);
}

void	unset(char **str)
{
	int	i;
	int	j;

	i = 0;
	if (!str)
		return ;
	else
	{
		while (str[i])
		{
			j = ret_indice_env(g_data.ev, str[i]);
			if (j != -1)
				g_data.ev = delete_it(j);
			i++;
		}
	}
}
