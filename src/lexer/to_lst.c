/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   to_lst.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:29:00 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:34:01 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	cmd_type(char *cmd)
{
	if (*cmd == '|')
		return (C_PIPE);
	if (*cmd == '>')
	{
		if (*(cmd + 1) == '>')
			return (C_RDR_R_DBL);
		return (C_RDR_R);
	}
	if (*cmd == '<')
		return (C_RDR_L);
	if (*cmd == ';')
		return (C_END);
	return (-1);
}

static void	add_after_slash(int *mode, char *str, char **line)
{
	t_dlist *last;

	last = ft_dlstlast(g_data->lst);
	if (!stradd(&(((t_token *)(last->content))->str), str))
		parser_exit(ERRNO, line);
	((t_token *)(last->content))->len = \
						ft_strlen(((t_token *)(last->content))->str);
	*mode = 0;
}

void		to_lst(char *line, int start, int len, int *mode)
{
	t_token	*token;
	char	*str;

	if (!len)
		return ;
	if (!(str = ft_substr(line, start, len)))
		parser_exit(ERRNO, &line);
	if (*mode == '\\')
	{
		add_after_slash(mode, str, &line);
		return ;
	}
	if (!(token = (t_token *)malloc(sizeof(t_token))))
	{
		free(str);
		parser_exit(ERRNO, &line);
	}
	token->str = str;
	token->len = (*mode == 'C') ? cmd_type(str) : len;
	ft_dlstadd_back(&(g_data->lst), ft_dlstnew(token));
}
