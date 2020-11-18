/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/20 18:47:12 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/18 02:32:22 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXIT_H
# define EXIT_H

# include <errno.h>
# include <string.h>
#include "../libft/libft.h"

# define ERRNO -2
# define ERR_DEBUG -1

int	error_msg(char *filename, int code);

int	exit_with_errno(void);
int	exit_custom_err(int error_num);
int	free_and_exit(int error_num);

int		parse_line_exit(char *line, int error_num);
void	parser_exit(t_dlist **lst, char **str);

#endif
