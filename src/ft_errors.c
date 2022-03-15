/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:20:04 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/15 18:11:07 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"


int	ft_join_error(char *s1, char *s2, int Exit)
{
	char	*Err_msg;

	Err_msg = ft_strjoin(s1, s2);
	perror(Err_msg);
	free(Err_msg);
	return (Exit);
}

void ft_error_fd(char *str, int Exit)
{
	ft_putstr_fd(str, 2);
	exit(Exit);
}