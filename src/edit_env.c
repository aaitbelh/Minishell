/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   edit_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:47:09 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/16 14:14:18 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void edit_oldpwd()
{
	int		i;
	char	*old_path;
	int		j;

	old_path = getcwd(NULL, 0);
	i = ret_indice_env(g_data.ev, "OLDPWD=");
	printf("%d\n", i);
	j = 7;
	while(g_data.ev[i][j])
	{
		g_data.ev[i][j] = old_path[j - 7];
		j++;
	}
	free(old_path);
	
}
void	edit_pwd()
{
	int		i;
	int		j;
	char	*pwd;
	
	pwd = getcwd(NULL, 0);
	j = 0;
	i = ret_indice_env(g_data.ev, "PWD=");
	while(g_data.ev[i][j])
	{
		g_data.ev[i][j + 4] = pwd[j];
		j++;
	}
	free(pwd);
}