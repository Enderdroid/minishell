/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:22 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:18:11 by ttamesha         ###   ########.fr       */
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

static void	to_lst(char *line, int start, int len, int *mode)
{
	t_token	*token;
	t_dlist *last;
	char	*str;

	if (!len)
		return ;
	if (!(str = ft_substr(line, start, len)))
		parser_exit(ERRNO, &line);
	if (*mode == '\\')
	{
		last = ft_dlstlast(g_data->lst);
		if (!stradd(&(((t_token *)(last->content))->str), str))
			parser_exit(ERRNO, &line);
		((t_token *)(last->content))->len = \
							ft_strlen(((t_token *)(last->content))->str);
		*mode = 0;
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

static void	add_cmd(char *line, int *start, int *end)
{
	int mode;

	mode = 'C';
	if (line[*end] == '>' && (line[*end + 1] == '>' || line[*end + 1] == '|'))
		to_lst(line, (*end)++, 2, &mode);
	else if (!ft_isspace(line[*end]))
		to_lst(line, *end, 1, &mode);
	*start = *end + 1;
}

static int	quote_pair(char *input, int i)
{
	char quote;

	quote = input[i];
	while (input[++i])
	{
		if (input[i] == quote)
			break ;
		else if (input[i] == '\\' && quote == '\"' && input[i + 1])
			++i;
	}
	return (i);
}

int			split_line(char *line, int mode)
{
	int start;
	int end;

	end = (mode == '\\') ? 0 : -1;
	start = 0;
	while (line[++end])
	{
		if (line[end] == '\\' && line[end + 1])
			++end;
		else if ((line[end] == '\'' || line[end] == '\"'))
		{
			if (!line[end = quote_pair(line, end)])
				return (0);
		}
		else if (ft_strchr(METACHAR, line[end]))
		{
			to_lst(line, start, end - start, &mode);
			add_cmd(line, &start, &end);
		}
	}
	to_lst(line, start, end - start, &mode);
	return (1);
}
