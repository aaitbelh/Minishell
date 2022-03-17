/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 18:13:34 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/17 14:49:12 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void ft_strswap(char **s1, char **s2)
{
	char	*s3;
	
	s3 = *s1;
	*s1 = *s2;
	*s2 = s3;
}

void sort_it(char **table)
{
	int	i;
	int	j;

	i = 0;
	while(table[i])
	{
		j = i + 1;
		while(table[j])
		{
			if(ft_strcmp(table[i], table[j]) > 0)
				ft_strswap(&table[i], &table[j]);
			j++;
		}
		i++;
	}
}

char	**cpy_exp(char **env)
{
	char **sorted_env;
	int i;

	i = 0;
	while(env[i])
		i++;
	sorted_env = malloc((sizeof(char *) * i) + 1);
	i = 0;
	while(env[i])
	{
		sorted_env[i] = ft_strdup(env[i]);
		i++;	
	}
	sorted_env[i] = NULL;
	sort_it(sorted_env);
	return (sorted_env);
}
int	syntax_check(char *str)
{
	if(str[0] != '_' && !ft_isalpha(str[0]))
		return (1);
	return (0);
}