/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/02 13:36:56 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/29 10:25:16 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char *get_from_env(char *str, int size, int start)
{
	int	i;

	i = 0;
	while(g_data.ev[i])
	{
		if(!strncmp(g_data.ev[i], str, size))
			return (ft_substr(g_data.ev[i], start, ft_strlen(g_data.ev[i])));
		i++;
	}
	return (NULL);
}

int	check_is(char c, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(str[i] == c)
			return (-1);
		i++;
	}
	return (0);
}


int	is_there_space(char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if(!check_is(str[i], " \t\n\v\f\r"))
			break;
		i++;
	}
	if(!str[i])
		return(1);
	else
		return (0);
}

char **cpy_env(char **str)
{
	char **table;
	int	i;

	i = 0;
	while(str[i])
		i++;
	table = malloc(sizeof(char *) * (i + 1));
	if(!table)
		return (NULL);
	i = 0;
	while(str[i])
	{
		table[i] = ft_strdup(str[i]);
		i++;
	}
	table[i] = NULL;
	return(table);
}