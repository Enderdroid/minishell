/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signals.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:52 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/19 02:16:13 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parserstruct.h"

static void	handle_sigint(int signal)
{
	/*if (g_data->cur_process)
	{
		kill(g_data->cur_process, signal);
		g_code = 130;
		g_data->cur_process = 0;
	}
	else*/
	{
		write(1, "\n", 1);
		{
			g_code = 1;
			write(1, "minishell", 9);
			write(1, "> ", 2);
		}
	}

}

static void	handle_sigquit(int signal)
{
	/*if (g_data->cur_process)
	{
		kill(g_data->cur_process, signal);
		g_code = 131;
		write(2, "Quit: 3\n", 8);
		g_data->cur_process = 0;
	}
	else*/
	{
		write(1, "\b\b", 2);
	}

}

void			handle_signals(void)
{
	//if (signal(SIGINT, &handle_sigint) == SIG_ERR)
	//	;
	if (signal(SIGQUIT, &handle_sigquit) == SIG_ERR)
		;//??

}