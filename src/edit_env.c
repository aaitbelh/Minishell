/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: casper <casper@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:47:09 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/08/15 18:50:00 by casper           ###   ########.fr       */
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
	char	*old_path;
	char	*old_pwd;
	char	**tmp;

	old_path = getcwd(NULL, 0);
	if(!old_path)
		old_path = ft_strdup("");
	i = ind_from_env(g_data.ev, "OLDPWD=");
	if(i == -1)
	{
		tmp = malloc(sizeof(char *) * 2);
		tmp[0] = ft_strdup("OLDPWD=");
		tmp[1] = NULL;
		ft_export(tmp);
	}
	i = ind_from_env(g_data.ev, "OLDPWD=");
	old_pwd = ft_strjoin("OLDPWD=", old_path);
	free(old_path);
	free(g_data.ev[i]);
	g_data.ev[i] = ft_strdup(old_pwd);
	free(old_pwd);
}

void	edit_pwd(void)
{
	int		i;
	char	*new_pwd;
	char	*pwd;

	pwd = getcwd(NULL, 0);
	i = ind_from_env(g_data.ev, "PWD=");
	new_pwd = ft_strjoin("PWD=", pwd);
	free(g_data.ev[i]);
	g_data.ev[i] = ft_strdup(new_pwd);
	free(new_pwd);
	free(pwd);
}
