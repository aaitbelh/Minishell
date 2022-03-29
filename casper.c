/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   casper.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 21:13:53 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/03/16 21:38:37 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

void ft_strswap(char **s1, char **s2)
{
	char	*s3;
	
	s3 = *s1;
	*s1 = *s2;
	*s2 = s3;
}


int main()
{
	char *s1;
	char *s2;
	s1 = strdup("HELLO");
	s2 = strdup("WORLD");
	ft_strswap(&s1, &s2);
	printf("%s\n", s1);
	printf("%s\n", s2);
}