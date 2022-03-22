/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_build.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/21 22:04:47 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/22 15:29:54 by aaitbelh         ###   ########.fr       */
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
	while (args[i])
		i++;
	new_arg = malloc(sizeof(char *) * (i + 2));
	i = 1;
	new_arg[0] = ft_strdup(cmd);
	free(cmd);
	while(args[i - 1])
	{
		new_arg[i] = args[i - 1];
		i++; 	
	}
	new_arg[i] = NULL;
	twoDfree(args);
	return (new_arg);
}


int is_command()
{
	// int fd;
	char *cmd_path;
	cmd_path = ft_check_acs(g_data.ev,g_data.cmd->command);
	printf("%s\n", cmd_path);
	g_data.cmd->arg = fix_command(g_data.cmd->command, g_data.cmd->arg);
	// printf("%s ", lol[0]);
	// printf("%s ", lol[1]);
	// printf("%s\n", lol[2]);
	g_data.n--;
	// if(!g_data.cmd->file)
	// {
	// 	fd = open(g_data.cmd->file->file_name, O_RDONLY);
	// 	if(fd == -1)
	// 		return (ft_join_error("Minishell: ", g_data.cmd->file->file_name, 1));
	// 	dup2(fd, 0);
	// }
	// if(g_data.n != 0)
	// {
	// 	dup2(g_data.pipe[g_data.output], 1);
	// 	close(g_data.pipe[g_data.input]);
	// }
	execve(cmd_path, g_data.cmd->arg ,g_data.ev);
	return (0);
}