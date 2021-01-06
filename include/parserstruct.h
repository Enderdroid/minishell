/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parserstruct.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:01 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/06 18:33:31 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSERSTRUCT_H
# define PARSERSTRUCT_H

# include "libstruct.h"
# include <signal.h>

# define COLOR "\e[0;36m"
# define RESET "\e[0m"

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

void			parse_input(char unfinished);
void			free_tokens(t_dlist **lst);
void			print_list(t_dlist *lst); //del

#endif
