/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:22 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:28:52 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

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
