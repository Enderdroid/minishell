/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:01:44 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/09 06:16:26 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include <unistd.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "exit.h"
#include "libstruct.h"

#define METACHAR "|;<> \t\n" //&()

typedef struct	s_token
{
	char		*str;
	int			len;
}				t_token;

typedef struct	s_vld
{
	char		*prv;
	const char	*nxt[50];
}				t_vld;

void			parse_input(int unfinished, t_dlist **lst);
void			free_tokens(t_dlist **lst);
int				quote_pair(char *input, int i);
int				stradd(char **str, char *new);
void			correct_str(char **line, int *strlen, char **mask, t_dlist **lst);
int				get_tokens(t_dlist **lst, char *line, int last_char);
void			free_tokens(t_dlist **lst);
char			*str_mask(char *str, int len);
void			validate(t_dlist **lst, int q);

void			free_data(void);
void			init_data(char **envp);

void	print_list(t_dlist *lst);//
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
