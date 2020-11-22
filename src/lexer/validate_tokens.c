/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:29 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:21:41 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	unclosed_q_msg(void)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error: unclosed quote\n", 29);
	g_code = 258;
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
	if (token->str[token->len - 1] == '\\')
	{
		if (!(mask = str_mask(token->str, token->len)))
			parser_exit(ERRNO, NULL);
		if (mask[token->len - 1] == '0')
		{
			free(mask);
			parse_input('\\');
		}
		free(mask);
	}
}

void		validate_tokens(int q_closed)
{
	t_dlist	*last;
//printf("q %i\n", q_closed);// //printf("*%s, %i\n", ((t_token *)((*lst)->content))->str, ((t_token *)((*lst)->content))->len);
	last = NULL;
	check_syntax_error(&last);
	if (!q_closed)
		unclosed_q_msg();
	if (last)
		check_last((t_token *)(last->content));
	//printf("##%s\n", ((t_token *)((*lst)->content))->str);//
}
