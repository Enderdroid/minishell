/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   p_execute.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:28 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:28 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libincludes.h"
#include "../../include/error.h"

int			builtin_call(t_exec *exec)
{
	if (!(ft_strcmp(exec->name, "cd")))
		return (b_cd(exec));
	else if (!(ft_strcmp(exec->name, "echo")))
		return (b_echo(exec));
	else if (!(ft_strcmp(exec->name, "env")))
		return (b_env(exec));
	else if (!(ft_strcmp(exec->name, "exit")))
		return (b_exit(exec));
	else if (!(ft_strcmp(exec->name, "export")))
		return (b_export(exec));
	else if (!(ft_strcmp(exec->name, "pwd")))
		return (b_pwd(exec));
	else if (!(ft_strcmp(exec->name, "unset")))
		return (b_unset(exec));
	else
		return (-1);
}

static int	sub_exec(t_exec *exec, int *rv)
{
	int		pid;
	int		ret;

	if (exec->full_name)
	{
		if (!(pid = fork()))
		{
			ret = execve(exec->full_name, exec->argv, g_data->l_env);
			if (ret == -1 && ERRNO == -2)
				error_msg_auto(rv, exec->full_name, 126);
			free_and_exit(*rv);
		}
		g_data->pid = pid;
		return (0);
	}
	return (1);
}

int			ft_execute(t_exec *exec)
{
	int		rv;
	int		ret;

	rv = 0;
	if (sub_exec(exec, &rv))
		rv = builtin_call(exec);
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
