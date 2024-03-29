/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casper <casper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 17:26:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/15 18:26:51 by casper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*fix_for_plus(char *str)
{
	char	*new_str;
	int		i;
	int		j;
	int		ind;

	j = 0;
	i = 0;
	ind = 0;
	while (str[ind] != '+')
		ind++;
	new_str = malloc(sizeof(char ) * ft_strlen(str));
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (i != ind)
		{
			new_str[j] = str[i];
			j++;
		}
		i++;
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

void	is_plus(char *str)
{
	int		i;
	char	**new_str;

	i = 0;
	if (check_syn_pls(str))
	{
		join_th_errors_re("minishell: export: ", str,
			": not valid inddentifier", 1);
		free(str);
		return ;
	}
	new_str = ft_split(str, '+');
	while (g_data.ev[i])
	{
		if (check_exist(str, i, new_str))
			return ;
		i++;
	}
	twodfree(new_str);
	str = fix_for_plus(str);
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
	if (!new_env)
		return (NULL);
	i = 0;
	while (g_data.ev[i])
	{
		new_env[i] = ft_strdup(g_data.ev[i]);
		i++;
	}
	new_env[i] = ft_strdup(str);
	new_env[i + 1] = NULL;
	twodfree(g_data.ev);
	free(str);
	return (new_env);
}

void	add_bath_evx(char *string)
{
	int		i;
	char	**path;
	char	*str;

	str = ft_strdup(string);
	path = ft_split(str, '=');
	if (path[0][ft_strlen(path[0]) - 1] == '+')
	{
		is_plus(str);
		twodfree(path);
		return ;
	}
	i = 0;
	while (g_data.ev[i])
	{
		if (check_exist2(str, i, path))
			return ;
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
		{
			add_bath_evx(path[i]);
		}
		i++;
	}
	return (0);
}
