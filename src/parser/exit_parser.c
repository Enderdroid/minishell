/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/14 19:28:41 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/14 22:02:57 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exit.h"
#include "../../include/parser.h"
#include "../../libft/libft.h"

void	parser_exit(t_dlist **lst, char **str) //, int error_num
{
	free_tokens(lst);
	if (*str)
		free(*str);
	free_and_exit(ERRNO);
	exit(-1);
}

int	exit_with_errno(void)
{
	ft_putendl_fd(strerror(errno), 1);
	g_code = errno;//?
	exit(errno);
}

int	free_and_exit(int error_num)
{
	free_data();
	if (error_num == ERRNO)
		return (exit_with_errno());
	else
	{
		g_code = error_num;
		return (exit_custom_err(error_num));
	}
}

int	exit_custom_err(int error_num)
{
	if (error_num == ERR_DEBUG)
		write(1, "Error\nSomething went wrong\n", 27);
	exit(error_num);
}

int	parse_line_exit(char *line, int fd, int error_num)
{
	if (line)
		free(line);
	close(fd);
	return ((free_and_exit(error_num)));
}
