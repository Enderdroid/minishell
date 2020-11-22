/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:18:11 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:26:19 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

static int	paste_env(char *str, int *start, int *end, char **res)
{
	char *new;

	if (str[*start] == '$' && !ft_isalpha(str[*end]) && !ft_strchr("_?", str[*end]))
		*start = *end + 1;
	else
	{
		if (str[*start] == '~')
		{
			new = find_env(ft_strdup("HOME"));
			*start = (*end)--;
		}
		else if (str[*end] == '?')
		{
			new = ft_itoa(g_code);
			*start = *end + 1;
		}
		else
		{
			while (ft_isalpha(str[*end]) || \
					ft_isdigit(str[*end]) || str[*end] == '_')
				++(*end);
			new = find_env(ft_substr(str, *start + 1, *end - *start - 1));
			*start = (*end)--;
		}
		if (!stradd(res, new))
			return (0);
	}
	return (1);
}

static char	*substr_filtered(char *str, char *mask, int len, int end)
{
	char	*res;
	int		start;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	//printf("%s\n, %s\n", str, mask);
	i = 0;
	start = 0;
	while (start < end)
	{//printf("%c, %c\n", mask[start], str[start]);
		if (mask[start] == '1')
		{
			res[i] = str[start];
			//printf("%c,%i,%c\n", res[i], start, str[start]);
			++i;
		}
		++start;
	}
	res[i] = '\0';
	//printf("%s\n", res);//
	return (res);
}

static void	correct_str(t_token *token, char **res, char **mask)
{
	int		end;
	int		start;
	int		len;

	end = -1;
	start = 0;
	len = 0;
	while (++end <= token->len)
	{
		if ((*mask)[end] == '1')
			++len;
		else if (end == token->len && token->len == len)
			free_and_null(res);
		else if (ft_strchr("$~\0", (*mask)[end]))
		{
			if (len > 0)
				if (!stradd(res, substr_filtered(token->str + start, \
						*mask + start, len, end - start)))
					parser_exit(ERRNO, mask);
			if ((*mask)[start = end++] == '$' || (*mask)[start] == '~')
				if (!paste_env(token->str, &start, &end, res))
					parser_exit(ERRNO, mask);
		}
	}
}

static char	*corrected_str(t_token *token)
{
	char *mask;
	char *res;

	if (!(mask = str_mask(token->str, token->len)))
		parser_exit(ERRNO, NULL);
	if (!(res = ft_strdup("")))
		parser_exit(ERRNO, &mask);
	correct_str(token, &res, &mask);
	printf("mask=%s\n", mask);//
	free(mask);
	if (res && !ft_strcmp(res, "\0") &&
		!(ft_strchr(token->str, '\'') || \
		ft_strchr(token->str, '\"')))
	{
		token->len = 0;
		free(res);
		res = NULL;
	}
	else
		token->len = 1;
	return (res);
}

void		correct_tokens(void)
{
	t_dlist	*lptr;
	char	*newstr;

	lptr = g_data->lst;
	while (lptr)
	{
		if (((t_token *)(lptr->content))->len > 0)
		{
			if ((newstr = corrected_str((t_token *)(lptr->content))))
			{
				free(((t_token *)(lptr->content))->str);
				((t_token *)(lptr->content))->str = newstr;
			}
		}
		lptr = lptr->next;
	}
}
