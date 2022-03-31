/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 14:17:04 by alaajili          #+#    #+#             */
/*   Updated: 2022/03/31 02:06:08 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_error(int i, int k)
{
	if (g_data.cmds[i][k] == '>' && g_data.cmds[i][k + 1] == '<')
	{
		write(1, "minishell: syntax error near unexpected token `<'\n", 50);
		g_data.num_of_args[i] = 0;
		g_data.num_of_files[i] = 0;
		return (0);
	}
	if (g_data.cmds[i][k] == '<' && g_data.cmds[i][k + 1] == '>')
	{
		write(1, "minishell: syntax error near unexpected token `>'\n", 50);
		g_data.num_of_args[i] = 0;
		g_data.num_of_files[i] = 0;
		return (0);
	}
	return (1);
}

int	check_error_2(int i, int k)
{
	if (g_data.cmds[i][k] == '>')
	{
		write(1, "minishell: syntax error near unexpected token `>'\n", 50);
		g_data.num_of_args[i] = 0;
		g_data.num_of_files[i] = 0;
		return (0);
	}
	if (g_data.cmds[i][k] == '<')
	{
		write(1, "minishell: syntax error near unexpected token `<'\n", 50);
		g_data.num_of_args[i] = 0;
		g_data.num_of_files[i] = 0;
		return (0);
	}
	return (1);
}

int	skip_quotes(int i, int k)
{
	if (g_data.cmds[i][k] == 34)
	{
		k++;
		while (g_data.cmds[i][k] != 34)
			k++;
	}
	else if (g_data.cmds[i][k] == 39)
	{
		k++;
		while (g_data.cmds[i][k] != 39)
			k++;
	}
	return (k);
}

static int	to_the_next(int i, int k)
{
	while (g_data.cmds[i][k] != ' ' && g_data.cmds[i][k] != '>'
			&& g_data.cmds[i][k] != '<' && g_data.cmds[i][k])
	{
		k = skip_quotes(i, k);
		k++;
	}
	return (k);
}

void	get_num_of_args_files(int i, int k)
{
	while (g_data.cmds[i][k])
	{
		while (g_data.cmds[i][k] == ' ')
			k++;
		if (g_data.cmds[i][k] == '>' || g_data.cmds[i][k] == '<')
		{
			g_data.num_of_files[i]++;
			if (check_error(i, k) == 0)
				return ;
			if (g_data.cmds[i][k + 1] == '>' || g_data.cmds[i][k + 1] == '<')
				k += 2;
			else
				k++;
			while (g_data.cmds[i][k] == ' ')
				k++;
			if (check_error_2(i, k) == 0)
				return ;
		}
		else if (g_data.cmds[i][k])
			g_data.num_of_args[i]++;
		while (g_data.cmds[i][k] == ' ')
			k++;
		k = to_the_next(i, k);
	}
}
