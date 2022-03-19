/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 18:42:20 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/18 22:05:13 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **delete_it(int	ind)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	char **new_table;
	while(g_data.ev[i])
		i++;
	new_table = malloc(sizeof(char *) * i);
	i = 0;
	while(g_data.ev[i])
	{
		if(ind != i)
		{
			new_table[j] = ft_strdup(g_data.ev[i]);
			j++; 
		}
		i++;
	}
	twoDfree(g_data.ev);
	new_table[j] = NULL;
	return (new_table);
}

void unset(char **str)
{
	int i;
	int	j;

	i = 1;
	if(!str[1])
		return ;
	else
	{
		while(str[i])
		{
			j = ret_indice_env(g_data.ev, str[i]);
			if(j != -1)
				g_data.ev = delete_it(j);
			i++;
		}
	}
}