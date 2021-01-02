/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   b_exit.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/29 23:02:32 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/03 00:39:30 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libbuiltins.h"
#include "../../include/error.h"

static int	code_extracted(char *s)
{
	long long	nb;
	int			invalid;
	int			sign;

	while (ft_isspace(*s))
		s++;
	sign = (*s == '-') ? -1 : 1;
	if (*s == '+' || *s == '-')
		s++;
	invalid = (ft_isdigit(*s)) ? 0 : 1;
	nb = 0;
	while (ft_isdigit(*s))
	{
		nb = nb * 10 + sign * (*s++ - '0');
		if ((nb != 0) && ((nb > 0) != (sign > 0)))
			invalid = 1;
	}
	while (ft_isspace(*s))
		s++;
	if (invalid || *s)
		return (-1);
	return ((unsigned char)nb);
}

int			b_exit(t_exec *exec)
{
	if (!exec->pipe_from && !exec->pipe_to)
		write(1, "exit\n", 5);
	if (exec->argv[1])
	{
		if ((g_data->code = code_extracted(exec->argv[1])) == -1)
		{
			write(2, "minishell: exit: ", 17);
			ft_putstr_fd(exec->argv[1], 2);
			write(2, ": ", 2);
			write(2, "numeric argument required\n", 26);
			g_data->code = 255;
		}
		else if (exec->argv[2])
		{
			error_msg_custom(&exec->ret, "exit", "too many arguments", 1);
			return (0);
		}
	}
	else
		g_data->code = 0;
	free_and_exit(g_data->code);
	return (0);
}
