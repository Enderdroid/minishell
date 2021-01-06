/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:45:18 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/06 21:54:00 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	syntax_err_msg(const char *token)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	write(2, "`", 1);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	g_data->code = 258;
	free_tokens(&(g_data->lst));
	parse_input(0);
	return (0);
}

static void	check_token(char *prv, char *nxt)
{
	int			i;
	int			j;
	const t_vld	vld[7] = { {"\0", {";", "|", NULL} }, \
				{";", {"|", ";", NULL} }, \
				{">>", {">|", "newline", ">", "<", ">>", ";", "|", NULL} }, \
				{">|", {">|", "newline", ">", "<", ">>", ";", "|", NULL} }, \
				{"|", {";", "|", NULL} }, \
				{">", {"<", ";", "newline", NULL} }, \
				{"<", {"<", ";", "|", "newline", ">", ">|", ">>", NULL} }, };

	i = -1;
	while (++i < 7)
	{
		j = -1;
		if (!ft_strcmp(prv, vld[i].prv))
		{
			while (vld[i].nxt[++j])
				if (!ft_strcmp((char *)(vld[i].nxt[j]), nxt))
					syntax_err_msg(vld[i].nxt[j]);
		}
	}
}

void		check_syntax_error(t_dlist **last)
{
	t_dlist	*ptr;
	char	*nxt;

	if ((ptr = g_data->lst))
	{
		if (((t_token *)(ptr->content))->len < 0)
			check_token("\0", ((t_token *)(ptr->content))->str);
		while (ptr)
		{
			if (((t_token *)(ptr->content))->len < 0 && \
				(!(ptr->next) || ((t_token *)(ptr->next->content))->len < 0))
			{
				nxt = (ptr->next) ? \
						((t_token *)(ptr->next->content))->str : "newline";
				check_token(((t_token *)(ptr->content))->str, nxt);
			}
			if (!ptr->next)
				*last = ptr;
			ptr = ptr->next;
		}
	}
}
