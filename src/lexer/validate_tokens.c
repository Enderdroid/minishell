/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:29 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/03 18:56:15 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	unclosed_q_msg(void)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error: unclosed quote\n", 29);
	g_data->code = 258;
	if (g_data->lst)
		free_tokens(&(g_data->lst));
	parse_input(0);
	return (0);
}

static void	check_last(t_token *token)
{
	char *mask;

	if (token->len == C_PIPE)
		parse_input('|');
	if (token->len > 0 && token->str[token->len - 1] == '\\')
	{
		if (!(mask = str_mask(token->str, token->len)))
			free_and_exit(ERRNO);
		if (mask[token->len - 1] == '0')
		{
			free(mask);
			parse_input('\\');
		}
		else
			free(mask);
	}
}

void		validate_tokens(int q_closed)
{
	t_dlist	*last;

	last = NULL;
	check_syntax_error(&last);
	if (!q_closed)
		unclosed_q_msg();
	if (last)
		check_last((t_token *)(last->content));
}
