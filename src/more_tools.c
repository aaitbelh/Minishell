/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   more_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 11:55:25 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/18 18:40:25 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ret_indice_env(char **env, char *str)
{
	int	i;

	i = 0;
	while(env[i])
	{
		if(!strncmp(env[i], str, ft_strlen(str)))
			return (i);
		i++;
	}
	return (-1);
}
