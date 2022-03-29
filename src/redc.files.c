/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redc.files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:42:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/29 15:50:06 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	red_files(t_cmd *cmd, int i)
{
	int	j;
	int	fd;

	j = 0;
	while(g_data.num_of_files[i] && j < g_data.num_of_files[i])
	{
		if (g_data.num_of_files[i] && cmd->file[j].file_type == 0)
		{
			fd = open(g_data.cmd->file[j].file_name, O_RDONLY);
			if (fd == -1)
				exit(ft_join_error("Minishell: ", cmd->file[j].file_name, 1));
			dup2(fd, 0);
		}
		else if(g_data.num_of_files[i] && cmd->file[j].file_type == 1)
		{
			fd = open(cmd->file[j].file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd == -1)
				exit(ft_join_error("Minishell: ", cmd->file[j].file_name, 1));
			dup2(fd, 1);
		}
		j++;
	}
}