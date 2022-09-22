/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casper <casper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:47:09 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/09/22 12:09:16 by casper           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
int	ind_from_env(char **env, char *str)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (!ft_strncmp(env[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}

void	edit_oldpwd(void)
{
	int		i;
	char	**tmp;

	i = ind_from_env(g_data.ev, "OLDPWD=");
	if(i == -1)
	{
		tmp[0] = "OLDPWD=";
		tmp[1] = NULL;
		ft_export(tmp);
	}
	i = ind_from_env(g_data.ev, "OLDPWD=");
	free(g_data.ev[i]);
	g_data.ev[i] = ft_strdup(g_data.old_pwd);
}

void	edit_pwd(void)
{
	int		i;
	char	*new_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if(!pwd)
		pwd = ft_strdup(g_data.old_path);
	else
	{
		free(g_data.old_path);
		g_data.old_path = ft_strdup(pwd);
	}
	i = ind_from_env(g_data.ev, "PWD=");
	new_pwd = ft_strjoin("PWD=", pwd);
	free(g_data.ev[i]);
	g_data.ev[i] = ft_strdup(new_pwd);
	free(new_pwd);
	free(pwd);
}
