/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserstruct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:01 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/03 15:22:07 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERSTRUCT_H
# define PARSERSTRUCT_H

# include "libstruct.h"
#include <signal.h>
typedef struct	s_token
{
	char		*str;
	int			len;
}				t_token;

enum
{
	C_PIPE = -2,
	C_RDR_R = -3,
	C_RDR_L = -4,
	C_RDR_R_DBL = -5,
	C_END = -6,
};

void			parse_input(int unfinished);
void			free_tokens(t_dlist **lst);

//int				stradd(char **str, char *new);
void			print_list(t_dlist *lst); //del

#endif
