/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:56 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/19 02:11:45 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "parserstruct.h"

# define METACHAR "|;<> \t\n"

typedef struct	s_vld
{
	char		*prv;
	const char	*nxt[50];
}				t_vld;

void			correct_tokens(t_dlist **lst);
int				split_line(t_dlist **lst, char *line, int mode);
int				get_tokens(t_dlist **lst, char *line, int last_char);
char			*str_mask(char *str, int len);
void			check_syntax_error(t_dlist **lst, t_dlist **last);
void			validate_tokens(t_dlist **lst, int q);

#endif