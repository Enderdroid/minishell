/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catch_signals.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:52 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/06 18:33:12 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parserstruct.h"

static void	catch_sigint(int signal)
{
	if (g_data->pid)
	{
		kill(g_data->pid, signal);
		g_data->code = 130;
		g_data->pid = 0;
	}
	else
	{
		write(1, "\n", 1);
		{
			g_data->code = 1;
			ft_putstr_fd(COLOR, 1);
			write(1, "minishell", 9);
			ft_putstr_fd("> "RESET, 1);
		}
	}

}

static void	catch_sigquit(int signal)
{
	if (g_data->pid)
	{
		kill(g_data->pid, signal);
		g_data->code = 131;
		write(2, "Quit: 3\n", 8);
		g_data->pid = 0;
	}
	else
		write(1, "\b\b", 2);
}

void			catch_signals(void)
{
	if (signal(SIGINT, &catch_sigint) == SIG_ERR)
		free_and_exit(ERRNO);
	if (signal(SIGQUIT, &catch_sigquit) == SIG_ERR)
		free_and_exit(ERRNO);
}
