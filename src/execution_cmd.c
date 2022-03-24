/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:04:47 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/24 20:39:27 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char **fix_command(char *cmd, char **args)
{
	char	**new_arg;
	int i;
	int	j;

	i = 0;
	j = 1;	
	while (args && args[i])
		i++;
	new_arg = malloc(sizeof(char *) * (i + 2));
	i = 1;
	new_arg[0] = ft_strdup(cmd);
	free(cmd);
	while(args && args[i - 1])
	{
		new_arg[i] = args[i - 1];
		i++; 	
	}
	new_arg[i] = NULL;
	// twoDfree(args);
	return (new_arg);
}


int is_command(t_cmd *cmd, int i)
{
	int fd;
	int  ii = 0 ;
	char *cmd_path;
	cmd_path = ft_check_acs(g_data.ev, cmd->command);
	cmd->arg = fix_command(cmd->command, cmd->arg);
	g_data.n++;
	if(cmd->file && cmd->file->file_type == 0)
	{
		fd = open(g_data.cmd->file->file_name, O_RDONLY);
		if(fd == -1)
			exit(ft_join_error("Minishell: ", cmd->file->file_name, 1));
		dup2(fd, 0);
	}
	else if(cmd->file && cmd->file->file_type == 1)
	{
		fd = open(cmd->file->file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if(fd == -1)
			exit(ft_join_error("Minishell: ", cmd->file->file_name, 1));
		dup2(fd, 1);
	}
	if(g_data.number_cmd > 1)
	{
		if(i == 0)
		{
			close(g_data.pipe[g_data.input]);
			dup2(g_data.pipe[g_data.output], 1);
		}
		else if(i == g_data.number_cmd - 1)
		{
			dup2(g_data.pipe[g_data.input - 2], 0);
			while(ii < (g_data.number_cmd * 2) - 2)
			{
				close(g_data.pipe[ii]);
				ii++;
			}
		}
		else
		{
			dup2(g_data.pipe[g_data.input - 2], 0);
			dup2(g_data.pipe[g_data.output], 1);
			dup2(g_data.pipe[g_data.input], 0);
		}
	}
	execve(cmd_path, cmd->arg ,g_data.ev);
	return (0);
}