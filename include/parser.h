/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:01:44 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/06 01:57:32 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "libstruct.h"

t_env			*parse_env(char **envp, int *size);
t_u_env			parse_u_env(t_env *env, int size);
void			parse_input(t_env *env);
void			free_tokens(t_dlist **lst);
int				quote_pair(char *input, int i);
void			correct_str(char **line, int len, char *mask);
void			split_line(char *line, t_dlist **lst);
int				input_is_valid(char *input);

typedef struct	s_vld
{
	char		c;
	char		*after;
	const char	*feedback[50];
}				t_vld;

typedef struct	s_token
{
	char		*str;
	int			len;
}				t_token;
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
*/
#define METACHAR "|;<> \t\n" //&()

#endif
