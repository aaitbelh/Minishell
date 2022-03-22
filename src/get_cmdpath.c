/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:51:42 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/22 14:27:00 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	free_all(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

static int	find_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", ft_strlen("PATH=")))
			break ;
		i++;
	}
	return (i);
}

char	*ft_check_acs(char **env, char *cmd)
{
	char	**string;
	char	*check;
	int		j;

	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (cmd);
		else
			ft_error_ex("Permission denied error!!", 1);
	}
	cmd = ft_strjoin("/", cmd);
	j = find_path(env);
	string = ft_split(env[j] + 5, ':');
	j = 0;
	while (string[j])
	{
		check = ft_strjoin(string[j], cmd);
		if (!access(check, X_OK))
		{
			free(cmd);
			free_all(string);
			return (check);
		}
		j++;
		free(check);
	}
	free_all(string);
	if (access(cmd, F_OK != 0))
		ft_error_ex("command not found\n", 1);
	return (NULL);
}
