/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_cmdpath.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/22 12:51:42 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/01 09:54:29 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_is_path(char *cmd)
{
	if (access(cmd, F_OK) == 0)
	{
		if (access(cmd, X_OK) == 0)
			return (1);
		else
			ft_error_ex("Permission denied error!!\n", 1);
	}
	return (0);
}

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

char	**fin_and_split(char **env)
{
	int		j;
	char	**string;

	j = find_path(env);
	string = ft_split(env[j] + 5, ':');
	return (string);
}

char	*ft_check_acs(char **env, char *cmd)
{
	char	**string;
	char	*check;
	int		j;

	if (check_is_path(cmd))
		return (cmd);
	cmd = ft_strjoin("/", cmd);
	string = fin_and_split(env);
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
		join_th_errors("minishell: ", &cmd[1], ": command not found", 127);
	return (NULL);
}
