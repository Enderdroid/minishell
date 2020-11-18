/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/19 01:38:03 by ttamesha         ###   ########.fr       */
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
		if (!(data->exec = exec_init()))
			parser_exit(lst, NULL);
		newlst = exec_fill(lst, data->exec);
		free_tokens(lst);
		*lst = newlst;
		if (data->exec)
			//ft_processor(data->exec);
			free_exec(data->exec);//
			data->exec = NULL;//
	}
}

void	parse_line(char **line, t_dlist **lst, int last_char)
{
	int q_closed;

	q_closed = get_tokens(lst, *line, last_char);
	free(*line);
	*line = NULL;
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
	//line = ft_strdup("asa ; saa");//
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
		free(line);
		write(1, "exit\n", 5);
		free_and_exit(0);
	}
	//printf("do I ever get here?");//
	printf("gnl=%i, line = %s\n", ret, line);
}
