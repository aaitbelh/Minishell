/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:04:41 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/09 00:03:26 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void *x)
{
	t_list	*result;

	result = malloc(sizeof(t_list));
	if (!result)
		return (NULL);
	result->content = x;
	result->next = NULL;
	return (result);
}
