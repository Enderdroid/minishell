/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_init.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:04:54 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/02 23:04:56 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_exec	*exec_init(void)
{
	t_exec *exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->name = NULL;
	exec->path = NULL;
	exec->full_name = NULL;
	exec->argv = NULL;
	exec->env = g_data->l_env;
	exec->pipe_to = NULL;
	exec->pipe_from = NULL;
	exec->fd_new[0] = 0;
	exec->fd_new[1] = 1;
	exec->ret = 0;
	return (exec);
}
