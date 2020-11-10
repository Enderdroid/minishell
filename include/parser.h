/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:01:44 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/11 01:01:14 by ttamesha         ###   ########.fr       */
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

enum			cmd_type
{
	C_PIPE = -2,
	C_RDR_R = -3,
	C_RDR_L = -4,
	C_RDR_R_DBL = -5,
	C_END = -6,
};

void			parse_input(int unfinished, t_dlist **lst);
void			free_tokens(t_dlist **lst);
int				quote_pair(char *input, int i);
int				cmd_type(char *cmd);
int				stradd(char **str, char *new);
char			*corrected_str(t_dlist **lst, t_token *token);
int				get_tokens(t_dlist **lst, char *line, int last_char);
char			*str_mask(char *str, int len);
void			check_syntax_error(t_dlist **lst, t_dlist **last);
void			validate_tokens(t_dlist **lst, int q);
void			analise_tokens(t_dlist **lst);
t_dlist			*exec_fill(t_dlist **lst, t_exec *exec);

char			*find_env(char *key);
void			free_data(void);
void			free_exec(t_exec *exec);
void			init_data(char **envp);

void	print_list(t_dlist *lst);//del

#endif
