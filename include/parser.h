/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:01:44 by ttamesha          #+#    #+#             */
/*   Updated: 2020/10/25 20:31:10 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "libstruct.h"

int				input_is_valid(char *input);
t_env			*parse_env(char **envp, int *size);
t_u_env			parse_u_env(t_env *env, int size);
void			parse_input(void);

typedef struct	s_vld
{
	char			c;
	char			*after;
	const char		*feedback[50];
}				t_vld;

/*
enum TokenType{
	C_GENERAL = -1,
	C_PIPE = '|',
	C_AMPERSAND = '&',
	C_QOUTE = '\'',
	C_DQUOTE = '\"',
	C_SEMICOLON = ';',
	C_WHITESPACE = ' ',
	C_SLASH = '\\',
	C_TAB = '\t',
	C_NEWLINE = '\n',
	C_GREATER = '>',
	C_LESSER = '<',
	C_NULL = 0,

	TOKEN	= -1,
};

char metachar[] = {'|', '&', ';', '(', ')', '<', '>', ' ', '\t', '\n'};
*/

#endif
