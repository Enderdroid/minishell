/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_echo.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:50:59 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:50:59 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libbuiltins.h"

int			b_echo(t_exec *exec)
{
	int		ind;
	int		flag;

	flag = 0;
	ind = 0;
	while (exec->argv[++ind] && !(ft_strcmp(exec->argv[ind], "-n")))
		flag = 1;
	while (exec->argv[ind])
	{
		ft_putstr_fd(exec->argv[ind], exec->fd_new[1]);
		if (exec->argv[++ind])
			ft_putchar_fd(' ', exec->fd_new[1]);
	}
	if (!flag)
		ft_putstr_fd("\n", exec->fd_new[1]);
	return (0);
}
