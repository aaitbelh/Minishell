/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:26:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/18 18:39:31 by aaitbelh         ###   ########.fr       */
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
	new_env = malloc(sizeof(char *) * (i + 2));
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
	free(g_data.ev[i]);
	return (new_env);
}

void	add_bath_evx(char *str)
{
	int i;
	char **path;
	char **env_path;

	path = ft_split(str, '=');
	i = 0;	
	while(g_data.ev[i])
	{
		env_path = ft_split(g_data.ev[i], '=');
		if(!ft_strcmp(env_path[0], path[0]))
		{
			free(g_data.ev[i]);
			g_data.ev[i] = str;
			return ;
		}
		twoDfree(env_path);
		i++;
	}
	twoDfree(path);
	g_data.ev = add_new(str);
}

int ft_export(char **path)
{
	int i;
	i = 0;
	if(!path[1])
	{
		twoDfree(g_data.exp);
		g_data.exp = cpy_exp(g_data.ev);
		while(g_data.exp[i])
		{
			printf("declare -x %s\n", g_data.exp[i]);
			i++;
		}
		return(0);
	}
	i = 1;
	while(path[i])
	{ 
		if(syntax_check(path[i]))
			ft_join_error("Minishel: export: ", path[1], 1);
		else
			add_bath_evx(path[i]);
		i++;
	}
	return (0);
}