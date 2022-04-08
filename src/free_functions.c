/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/18 16:06:58 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/08 04:12:12 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	free_all_structs(void)
{
	int		i;
	int		j;

	i = 0;
	while (i < g_data.x + 1)
	{
		j = 0;
		free(g_data.cmd[i].command);
		twodfree(g_data.cmd[i].arg);
		while (j < g_data.num_of_files[i])
		{
			free(g_data.cmd[i].file[j].file_name);
			j++;
		}
		free(g_data.cmd[i].file);
		i++;
	}
	twodfree(g_data.cmds);
	free(g_data.num_of_args);
	free(g_data.num_of_files);
	free(g_data.cmd);
}

void	twodfree(char **table)
{
	int	i;

	i = 0;
	while (table[i])
	{
		free(table[i]);
		i++;
	}
	free(table);
}
