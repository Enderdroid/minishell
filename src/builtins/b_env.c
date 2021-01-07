/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_env.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:10 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:10 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libbuiltins.h"

static void	b_put_env(t_env *var, int fd)
{
	ft_putstr_fd(var->key, fd);
	ft_putstr_fd("=", fd);
	ft_putendl_fd(var->value, fd);
}

int			b_env(t_exec *exec)
{
	int		ind;

	ind = -1;
	while (g_data->env_arr[++ind])
		if (g_data->env_arr[ind]->value)
			b_put_env(g_data->env_arr[ind], exec->fd_new[1]);
	return (0);
}
