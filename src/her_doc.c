/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   her_doc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/14 16:11:17 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/31 23:43:47 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	her_doc(int *pipe, char *limiter)
{
	char	*str;

	while (1)
	{
		str = readline("> ");
		if (!str || !strcmp(str, limiter))
			break ;
		ft_putendl_fd(str, *pipe);
		free(str);
	}
	exit(0);
}

int	fork_for_herdoc(int *p, int i, int j)
{
	int	id;
	int	ret;

	id = fork();
	if (!id)
	{
		signal(SIGINT, SIG_DFL);
		her_doc(&p[1], g_data.cmd[i].file[j].file_name);
	}
	waitpid(id, &ret, 0);
	close(p[1]);
	if (WIFSIGNALED(ret))
	{
		close(p[0]);
		return (1);
	}
	g_data.cmd[i].p_herdoc = p[0];
	return (0);
}

int	is_there_herdoc(void)
{
	int	i;
	int	p[2];
	int	j;

	i = -1;
	while (++i < g_data.x + 1)
	{
		g_data.cmd[i].p_herdoc = -1;
		j = -1;
		while (++j < g_data.num_of_files[i])
		{
			if (g_data.cmd[i].file[j].file_type == 2)
			{
				pipe(p);
				if (g_data.cmd[i].p_herdoc != -1)
					close(g_data.cmd[i].p_herdoc);
				if (fork_for_herdoc(p, i, j))
					return (1);
			}
		}		
	}
	return (0);
}
