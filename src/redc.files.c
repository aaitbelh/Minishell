/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redc.files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 15:42:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/01 10:33:02 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	red_files_norm(t_cmd *cmd, int i, int j)
{
	int	fd;

	if (g_data.num_of_files[i] && cmd->file[j].file_type == 3)
	{
		fd = open(cmd->file[j].file_name,
				O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			exit(ft_join_error("minishell: ", cmd->file[j].file_name, 1));
		dup2(fd, 1);
	}
	else if (g_data.num_of_files[i] && cmd->file[j].file_type == 2)
	{
		dup2(cmd->p_herdoc, 0);
	}
}

void	red_files(t_cmd *cmd, int i)
{
	int	j;
	int	fd;

	j = 0;
	while (g_data.num_of_files[i] && j < g_data.num_of_files[i])
	{
		if (g_data.num_of_files[i] && cmd->file[j].file_type == 0)
		{
			fd = open(cmd->file[j].file_name, O_RDONLY);
			if (fd == -1)
				exit(ft_join_error("minishell: ", cmd->file[j].file_name, 1));
			dup2(fd, 0);
		}
		else if (g_data.num_of_files[i] && cmd->file[j].file_type == 1)
		{
			fd = open(cmd->file[j].file_name,
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				exit(ft_join_error("minishell: ", cmd->file[j].file_name, 1));
			dup2(fd, 1);
		}
		else
			red_files_norm(cmd, i, j);
		j++;
	}
}
