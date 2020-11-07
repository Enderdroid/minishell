/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/07 01:41:03 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

int	parse_line(char *line, t_dlist **lst) //ptr
{
	int err_q;

//	if (input_is_valid(line)) //do it via list after parsing
//	{
		err_q = split_line(line, lst);//err if unclosed
		//if (!validate(lst))// ptr
		//return (0);
		tokenize_lst(lst); //err_q?, ptr instead of lst //error if unfinished str
		//if (err_q)
		//	return (unclosed_q_msg());
//	}
	return (1);
}

void			parse_input() //int mode t_dlst **ptr
{
	int		ret;
	char	*line;
	t_dlist *lst;

	while ((ret = get_next_line(STDIN_FILENO, &line)) != 0 || *line)
	{//if (mode == 0)
		lst = NULL;
		if (parse_line(line, &lst)) //ptr //initialize ptr = lst
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
