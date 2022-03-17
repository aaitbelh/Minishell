/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:26:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/17 18:42:36 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


char **add_new(char *str)
{
	int		i;
	char	**new_env;

	i = 0;
	while(g_data.ev[i])
		i++;
	new_env = malloc(sizeof(char *) * i + 1);
	i = 0;
	while(g_data.ev[i])
	{
		new_env[i] = ft_strdup(g_data.ev[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	i = 0;
	while(g_data.ev[i])
	{
		free(g_data.ev[i]);
		i++;
	}
	// free(g_data.ev[i]);
	return (new_env);
}

void	add_bath_evx(char *str)
{
	int i;
	char **path;

	path = ft_split(str, '=');
	i = 0;	
	while(g_data.ev[i])
	{
		if(!ft_strncmp(g_data.ev[i], path[0], ft_strlen(path[0])))
		{
			printf("igot here it me im the probelmn")
			g_data.ev[i] = str;
			return ;
		}
		i++;
	}
	g_data.ev = add_new(str);
}

int ft_export(char **path)
{
	int i;
	i = 0;
	if(!path[1])
	{
		sort_it(g_data.exp);
		while(g_data.exp[i])
		{
			printf("declare -x %s\n", g_data.exp[i]);
			i++;
		}
		return(0);
	}
	while(path[i])
	{
		if(syntax_check(path[i]))
			return(ft_join_error("Minishel: export: ", path[1], 1));
		else
			add_bath_evx(path[i]);
		i++;
	}
	return (0);
}