/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alaajili <alaajili@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/10 15:19:59 by alaajili          #+#    #+#             */
/*   Updated: 2022/03/10 15:21:04 by alaajili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		if (s[i] && s[i] != c)
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static int	ft_len_word(char const *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static char	*ft_word(char const *s, char c)
{
	int		len;
	char	*str;
	int		i;

	i = 0;
	len = ft_len_word(s, c);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == 0)
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = 0;
	return (str);
}

static char	**ft_free(char **str, int i)
{
	while (i > 0)
	{
		i--;
		free((void *)str[i]);
	}
	free(str);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**str;
	int		i;

	if (!s)
		return (NULL);
	i = 0;
	str = (char **)malloc(sizeof(char *) * (ft_count_words(s, c) + 1));
	if (str == 0)
		return (NULL);
	while (*s)
	{
		if (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			str[i] = ft_word(s, c);
			if (str[i] == NULL)
				return (ft_free(str, i));
			i++;
		}
		while (*s && *s != c)
			s++;
	}
	str[i] = 0;
	return (str);
}
