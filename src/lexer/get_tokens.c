/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:18 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/03 18:54:04 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static void	del_last_token(t_dlist *last)
{
	if (last->prev)
		last->prev->next = NULL;
	if (((t_token *)(last->content))->str)
		free(((t_token *)(last->content))->str);
	free((t_token *)(last->content));
	free(last);
	last = NULL;
}

static int	pipe_before(t_dlist *last)
{
	return (!*(((t_token *)(last->content))->str + 1) && last->prev \
			&& ((t_token *)(last->prev->content))->len < 0 \
			&& *(((t_token *)(last->prev->content))->str) == '|');
}

static void	change_last_str(t_dlist *last, char **line)
{
	char	*tmp;

	tmp = ((t_token *)(last->content))->str;
	((t_token *)(last->content))->str = \
				ft_substr(tmp, 0, ((t_token *)(last->content))->len - 1);
	free(tmp);
	if (!((t_token *)(last->content))->str)
		parser_exit(ERRNO, line);
	if (!((t_token *)(last->content))->str[0])
	{
		if (!last->prev)
		{
			free_and_null(line);
			free_tokens(&g_data->lst);
			parse_input(0);
		}
		else
			del_last_token(last);
	}
}

int			get_tokens(char *line, int last_char)
{
	t_dlist	*last;

	if (last_char == '\\' && !*line)
	{
		last = ft_dlstlast(g_data->lst);
		if (pipe_before(last))
		{
			del_last_token(last);
			free(line);
			parse_input('|');
			return (1);
		}
		change_last_str(last, &line);
		return (1);
	}
	return (split_line(line, last_char));
}
