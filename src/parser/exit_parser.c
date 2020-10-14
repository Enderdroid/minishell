/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:28:41 by ttamesha          #+#    #+#             */
/*   Updated: 2020/10/14 22:30:21 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exit.h"
#include "../../libft/libft.h"

/*int	parser_exit(char **args, int error_num)
{
	//free_arr(args);
	//malloc_c(0);
	if (error_num == ERRNO)
		return (exit_with_errno());
	else
		return (exit_custom_err(error_num));
	exit(-1);
}*/

int	exit_with_errno(void)
{
	ft_putendl_fd(strerror(errno), 1);
	exit(errno);
}

int	free_and_exit(int error_num)
{
	//malloc_c(0);
	if (error_num == ERRNO)
		return (exit_with_errno());
	else
		return (exit_custom_err(error_num));
}

int	exit_custom_err(int error_num)
{
	if (error_num == ERR_DEBUG)
		write(1, "Error\nSomething went wrong\n", 27);
	exit(-1);
}
