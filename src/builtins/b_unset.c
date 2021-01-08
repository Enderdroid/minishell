/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_unset.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:25 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:25 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libbuiltins.h"

static int	u_is_env(char *arg)
{
	int		ind;

	ind = 0;
	if (!ft_isalpha(arg[ind]) && arg[ind] != '_')
		return (-1);
	while (arg[++ind])
		if (!ft_isalnum(arg[ind]) && arg[ind] != '_')
			return (-1);
	return (0);
}

int			b_unset(t_exec *exec)
{
	t_env	*env;
	int		i;
	int		code_buf;

	i = 0;
	code_buf = 0;
	while (exec->argv[++i])
	{
		if (u_is_env(exec->argv[i]) == -1)
		{
			code_buf = 1;
			b_put_error("unset", exec->argv[i], "not a valid identifier", 1);
			continue;
		}
		else if (!(g_data->pid))
		{
			env = find_env_b(exec->argv[i]);
			if (env)
				del_env(env);
		}
	}
	if (exec->argv[1] && !(g_data->pid))
		remake_lenv();
	return (code_buf);
}
