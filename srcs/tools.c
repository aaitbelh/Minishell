/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:36:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/10 14:27:37 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **cpy_env(char **str)
{
	char **table;
	int	i;
	int	j;

	i = 0;
	while(str[i])
		i++;
	table = malloc(sizeof(char *) * i);
	if(!table)
		return (NULL);
	i = 0;
	while(str[i])
	{
		j = 0;
		table[i] = malloc(sizeof(char ) *  strlen(str[i]));
		while(str[i][j])
		{
			table[i][j] = str[i][j];
			j++;
		}
		i++;
	}
	return(table);
}