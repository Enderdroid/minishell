/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 18:47:12 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/09 01:59:52 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <errno.h>
# include <string.h>
#include "../libft/libft.h"

# define ERRNO -1
# define ERR_DEBUG -2

int	exit_with_errno(void);
int	exit_custom_err(int error_num);
int	free_and_exit(int error_num);

int		parse_line_exit(char *line, int fd, int error_num);
void	parser_exit(t_dlist **lst, char **str);

#endif
