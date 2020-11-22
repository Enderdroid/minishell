/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 09:09:31 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"
#include "../../include/lexer.h"

void	analise_tokens(t_dlist **lst)
{
	t_dlist	*newlst;

	while (*lst)
	{
		if (!(g_data->exec = exec_init()))
			parser_exit(lst, NULL);
		newlst = exec_fill(lst, g_data->exec);
		free_tokens(lst);
		*lst = newlst;
		g_data->lst = lst;//?
		if (g_data->exec)
			//ft_processor(g_data->exec);
			free_exec(g_data->exec);//
			g_data->exec = NULL;
	}
	parse_input(0, lst);
}

void	parse_line(char **line, t_dlist **lst, int last_char)
{
	int q_closed;

	q_closed = get_tokens(lst, *line, last_char);
	free_and_null(line);
	print_list(*lst);//
	validate_tokens(lst, q_closed);
	correct_tokens(lst);
	print_list(*lst);//
	analise_tokens(lst);
	//free_tokens(lst);//
}

void	parse_input(int unfinished, t_dlist **lst)
{
	int		ret;
	char	*line;

	//line = ft_strdup("$\"PATH\"");//
	if (!*lst)
		write(1, "minishell", 9);
	write(1, "> ", 2);
	if ((ret = get_next_line(&line)) != 0)
	{//printf("gnl=%i\n", ret);//
		//printf("unfinished=%c\n", unfinished);//
		if (!*lst)
			unfinished = 0;
		parse_line(&line, lst, unfinished);
		return ;
	}
	if (ret == 0)
	{
		//printf("gnl=%i\n", ret);
		free_and_null(&line);
		write(1, "exit\n", 5);
		free_and_exit(0);
	}
	//printf("do I ever get here?");//
	printf("gnl=%i, line = %s\n", ret, line);
}
