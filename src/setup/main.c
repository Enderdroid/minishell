/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:22 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/06 21:57:09 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parserstruct.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_data(envp);

	while(42)
	{
		catch_signals();
		parse_input(0);
	}
}
