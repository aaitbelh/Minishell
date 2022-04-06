/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:26:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/06 17:58:23 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	is_plus(char *str)
{
	int		i;
	int		j;
	char	**new_str;
	char	**cmp;
	char	*tmp;

	i = 0;
	j = 0;
	while (str[j] != '=')
		j++;
	new_str = ft_split(str, '+');
	while (g_data.ev[i])
	{
		cmp = ft_split(g_data.ev[i], '=');
		if (!strcmp(cmp[0], new_str[0]))
		{
			tmp = ft_substr(str, j + 1, ft_strlen(str));
			g_data.ev[i] = ft_strjoin_gnl(g_data.ev[i], tmp);
			free(tmp);
			return ;
		}
		twodfree(cmp);
		i++;
	}
	g_data.ev = add_new(str);
}

char	**add_new(char *str)
{
	int		i;
	char	**new_env;

	i = 0;
	while (g_data.ev[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 2));
	i = 0;
	while (g_data.ev[i])
	{
		new_env[i] = ft_strdup(g_data.ev[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	i = 0;
	while (g_data.ev[i])
	{
		free(g_data.ev[i]);
		i++;
	}
	free(g_data.ev[i]);
	return (new_env);
}

void	add_bath_evx(char *str)
{
	int		i;
	char	**path;
	char	**env_path;

	path = ft_split(str, '=');
	if (path[0][ft_strlen(path[0]) - 1] == '+')
		return (is_plus(str));
	i = 0;
	while (g_data.ev[i])
	{
		env_path = ft_split(g_data.ev[i], '=');
		if (!ft_strcmp(env_path[0], path[0]))
		{
			free(g_data.ev[i]);
			g_data.ev[i] = str;
			return ;
		}
		twodfree(env_path);
		i++;
	}
	twodfree(path);
	g_data.ev = add_new(str);
}

int	ft_export(char **path)
{
	int	i;

	i = 0;
	if (!path[0])
	{
		print_the_exp();
		return (0);
	}
	while (path[i])
	{
		if (syntax_check(path[i]))
		{
			join_th_errors_re("minishell: export: ", path[i],
				": not valid inddentifier", 1);
		}
		else
			add_bath_evx(path[i]);
		i++;
	}
	return (0);
}
