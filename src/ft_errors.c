/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaitbelh <aaitbelh@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/13 13:20:04 by aaitbelh          #+#    #+#             */
/*   Updated: 2022/04/08 17:32:08 by aaitbelh         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	error_norm(char *str)
{
	join_th_errors("minishell: exit: ", str,
		": numeric argument required", 255);
}

int	join_th_errors(char *s1, char *s2, char *s3, int Exit)
{
	char	*tmp;
	char	*new;

	tmp = ft_strjoin(s1, s2);
	new = ft_strjoin(tmp, s3);
	free(tmp);
	ft_putendl_fd(new, 2);
	free(new);
	exit(Exit);
}

int	ft_error_ret(char *str, int ret)
{
	ft_putendl_fd(str, 2);
	g_data.ret = ret;
	return (ret);
}

int	join_error(char *s1, char *s2, int Exit)
{
	char	*err_msg;

	err_msg = ft_strjoin(s1, s2);
	perror(err_msg);
	free(err_msg);
	g_data.ret = Exit;
	return (Exit);
}

void	ft_error_ex(char *str, int Exit)
{
	ft_putstr_fd(str, 2);
	g_data.ret = Exit;
	exit(Exit);
}
