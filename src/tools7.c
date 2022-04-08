/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools7.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/08 01:44:19 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/08 04:08:03 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_syn_pls(char *string)
{
	int	i;
	int	j;

	j = 0;
	while (string[j] != '=')
		j++;
	i = 1;
	if (!string || (string[0] != '_' && !ft_isalpha(string[0])))
		return (1);
	while (i < j - 1)
	{
		if (!ft_isalnum(string[i]) && string[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	check_exist2(char *str, int i, char **path)
{
	char **env_path;

	env_path = ft_split(g_data.ev[i], '=');
	if (!ft_strcmp(env_path[0], path[0]))
	{
		free(g_data.ev[i]);
		twodfree(env_path);
		twodfree(path);
		g_data.ev[i] = str;
		return (1);
	}
	twodfree(env_path);
	return (0);
}

int	check_exist(char *str, int i, char **new_str)
{
	char	*tmp;
	char	**cmp;
	int		j;

	j = 0;
	while (str[j] != '=')
		j++;
	cmp = ft_split(g_data.ev[i], '=');
	if (!strcmp(cmp[0], new_str[0]))
	{
		tmp = ft_substr(str, j + 1, ft_strlen(str));
		g_data.ev[i] = ft_strjoin_gnl(g_data.ev[i], tmp);
		twodfree(new_str);
		twodfree(cmp);
		free(str);
		free(tmp);
		return (1);
	}
	twodfree(cmp);
	return (0);
}
