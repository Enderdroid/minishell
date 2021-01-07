/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_pwd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:22 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:22 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libbuiltins.h"

int			b_pwd(t_exec *exec)
{
	char	path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_putendl_fd(path, exec->fd_new[1]);
	return (0);
}
