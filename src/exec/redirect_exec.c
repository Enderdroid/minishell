/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_exec.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:33 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:33 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libincludes.h"
#include "../../include/error.h"

static int	r_sub_exec(t_exec *exec, int p_fd[2], int *rv)
{
	int		pid;
	int		ret;

	*rv = 0;
	if (!(pid = fork()))
	{
		if (p_fd[0] != 0)
			dup2(p_fd[0], 0);
		if (p_fd[1] != 1)
			dup2(p_fd[1], 1);
		if (p_fd[0] != 0)
			close(p_fd[0]);
		if (p_fd[1] != 1)
			close(p_fd[1]);
		ret = execve(exec->full_name, exec->argv, g_data->l_env);
		if (ret == -1 && ERRNO == -2)
			error_msg_auto(rv, exec->full_name, 126);
		free_and_exit(*rv);
	}
	else
		return (-1);
	g_data->pid = pid;
	return (0);
}

int			redir_execute(t_exec *exec)
{
	int		rv;
	int		ret;

	rv = 0;
	if (exec->full_name)
		r_sub_exec(exec, exec->fd_new, &rv);
	else
		rv = builtin_call(exec);
	if (exec->fd_new[0] != 0)
		close(exec->fd_new[0]);
	if (exec->fd_new[1] != 1)
		close(exec->fd_new[1]);
	if (exec->full_name)
	{
		waitpid(g_data->pid, &rv, 0);
		g_data->pid = 0;
		ret = WEXITSTATUS(rv);
	}
	else
		ret = rv;
	return (ret);
}
