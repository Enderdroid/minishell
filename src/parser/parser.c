/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/04 03:09:12 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

char	*add_str(char *line, char *res, int start, int end)
{
	char *new;
	char *tmp;

	new = ft_substr(line, start, end - start);
	//if (!new)
	//ERROR
	tmp = res;
	res = ft_strjoin(tmp, new);
	//if (!res)
	//ERROR
	free(tmp);
	free(new);
	return (res);
}

void	to_lst(t_dlist **lst, char *str, int len)
{
	t_token *token;

	token = malloc(sizeof(t_token *));
	printf("!%s\n", str);//
	//if (!str)
	//ERROR
	token->str = str;
	token->len = len;
	//if (*lst)
	//	printf("*!%s\n", ((t_token *)((*lst)->content))->str);
	ft_dlstadd_back(lst, ft_dlstnew(token));
	//printf("#%s\n", ((t_token *)((*lst)->content))->str);
}

void	split_line(char *line, t_dlist **lst)
{
	int start;
	int end;
	int len;

	end = -1;
	start = 0;
	while(line[++end])
	{
		if ((line[end] == '\'' || line[end] == '\"') && esc_seq(line, end))
		{	end = quote_pair(line, end);
			//printf("s=%c,e=%c,%i,%i\n", line[start], line[end], start, end);
		}
		else if (ft_strchr(METACHAR, line[end]) && esc_seq(line, end))
		{
			if ((len = end - start) > 0)
			{	to_lst(lst, ft_substr(line, start, len), len); // add to lst, check quotes \ $ //malloc protection in next func - ok with errno?
				//printf("?%s\n", ((t_token *)((*lst)->content))->str);
			}
			if (line[end] == '>' && (line[end + 1] == '>' || line[end + 1] == '|'))
				to_lst(lst, ft_substr(line, end++, 2), -1); //add to lst as cmd
			else if (!ft_isspace(line[end]))
				to_lst(lst, ft_substr(line, end, 1), -1); //add to lst as cmd
			//printf("s=%c,e=%c\n", line[start], line[end]);
			start = end + 1;
			//printf("s1=%c,e1=%c\n", line[start], line[end]);
		}
	}
	if ((len = end - start) > 0)
		to_lst(lst, ft_substr(line, start, len), len); // add to lst, check quotes \ $ //malloc protection in next func - ok with errno?
	//printf("-%s\n", ((t_token *)((*lst)->content))->str);
	//printf("-%s\n", ((t_token *)((*lst)->next->content))->str);
}

int	parse_line(char *line, t_env *env, t_dlist **lst)
{
//	if (input_is_valid(line)) //do it via list after parsing
	{
		split_line(line, lst);
		return (1); //if line is empty?
	}
	return (0);
}

void			parse_input(t_env *env)
{
	int		ret;
	char	*line;
	t_dlist *lst;

	while ((ret = get_next_line(STDIN_FILENO, &line)) != 0 || *line)
	{
		lst = NULL;
		if (parse_line(line, env, &lst))
		{
			//analise_lst(lst); //if nothing to analise return
			//free_and_exit();
		}
		//else
	}
	if (ret == 0)
	{
		//free(line);
		//free_and_exit();
	}
	free(line);
}


/*
t_exec analise_lst(t_dlist *lst)
{
	//static?
}

{
		analise_lst
	else
		parse_input
}
*/
