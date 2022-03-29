/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:04:47 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/29 15:55:23 by aaitbelh         ###   ########.fr       */
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
	// free(cmd);
	while(args && args[i - 1])
	{
		new_arg[i] = args[i - 1];
		i++; 	
	}
	new_arg[i] = NULL;
	return (new_arg);
}


int is_command(t_cmd *cmd, int i)
{
	char *cmd_path;

	cmd->ev = g_data.ev;
	if(g_data.x >= 1)
	{
		if(i == 0)
		{
			close(g_data.pipe[g_data.input]);
			dup2(g_data.pipe[g_data.output], 1);
		}
		else if(i == g_data.x)
		{
			dup2(g_data.pipe[g_data.input - 2], 0);
		}
		else
		{
			dup2(g_data.pipe[g_data.output], 1);
			dup2(g_data.pipe[g_data.input - 2], 0);
			close(g_data.pipe[g_data.input]);
		}
	}
	red_files(cmd, i);
	if (wh_typeit(cmd))
		exit(1);
	cmd_path = ft_check_acs(g_data.ev, cmd->command);
	cmd->arg = fix_command(cmd->command, cmd->arg);
	if((execve(cmd_path, cmd->arg,cmd->ev)) == -1)
		return (0);
		
	return (0);
}