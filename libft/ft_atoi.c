/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 16:12:55 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/30 15:36:37 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

long	ft_atoi(char *str)
{
	int						i;
	int						sig;
	unsigned long long int	n;

	sig = 1;
	n = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	if (str[i] == '-' || str[i] == '+' )
	{
		if (str[i] == '-')
			sig *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		n = n * 10 + (str[i] - '0');
		i++;
		if (n > 9223372036854775807 && sig == 1)
			join_th_errors("minishell: exit: ", str, ": numeric argument required", 255);
		if (n > 9223372036854775807 && sig == -1)
			join_th_errors("minishell: exit: ", str, ": numeric argument required", 255);
	}
	return ((n * sig));
}
