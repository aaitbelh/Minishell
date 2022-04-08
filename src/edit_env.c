/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:47:09 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/08 00:25:39 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	edit_oldpwd(void)
{
	int		i;
	char	*old_path;
	char	*old_pwd;

	old_path = getcwd(NULL, 0);
	i = ret_indice_env(g_data.ev, "OLDPWD=");
	old_pwd = ft_strjoin("OLDPWD=", old_path);
	free(old_path);
	free(g_data.ev[i]);
	g_data.ev[i] = old_pwd;
	free(old_pwd);
}

void	edit_pwd(void)
{
	// int		i;
	// char	*new_pwd;
	// char	*pwd;

	// pwd = getcwd(NULL, 0);
	// i = ret_indice_env(g_data.ev, "PWD=");
	// new_pwd = ft_strjoin("PWD=", pwd);
	// // free(g_data.ev[i]);
	// g_data.ev[i] = ft_strdup(new_pwd);
	// free(new_pwd);
	// free(pwd);
}
