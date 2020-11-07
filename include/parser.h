/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:01:44 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/07 01:47:23 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "libstruct.h"

#define METACHAR "|;<> \t\n" //&()

typedef struct	s_token
{
	char		*str;
	int			len;
}				t_token;

typedef struct	s_vld
{
	char		*prev;
	char		*after;
	const char	*feedback[50];
}				t_vld;

void			init_data(char **envp);
void			parse_input();
void			free_tokens(t_dlist **lst);
int				quote_pair(char *input, int i);
void			correct_str(char **line, int *strlen, char **mask);
int				split_line(char *line, t_dlist **lst);
void			free_tokens(t_dlist **lst);
void			tokenize_lst(t_dlist **lst);

void	free_data(void);
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

#endif
