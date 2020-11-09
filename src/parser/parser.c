/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/09 06:15:06 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

void	correct_tokens(t_dlist **lst)
{
	t_dlist	*ptr;
	char	*mask;

	ptr = *lst;
	while (ptr)
	{
		if (((t_token *)(ptr->content))->len > 0)
		{
			mask = str_mask((((t_token *)(ptr->content))->str), ((t_token *)(ptr->content))->len);
			if (!mask)
				parser_exit(lst, NULL);
			printf("%s - mask\n", mask);//
			correct_str(&(((t_token *)(ptr->content))->str), &(((t_token *)(ptr->content))->len), &mask, lst);
			printf("%s\n", ((t_token *)(ptr->content))->str);//
		}
		ptr = ptr->next;
	}
}

int		parse_line(char *line, t_dlist **lst, int last_char)
{
	int q_closed;

	q_closed = get_tokens(lst, line, last_char);
	free(line);
	print_list(*lst);//
	validate(lst, q_closed);
	correct_tokens(lst);
	print_list(*lst);//
	if (!*lst)  //if nothing to analise return to input
		parse_input(0, lst);
	//create struct exec

	free_tokens(lst);
	return (1);
}

void	parse_input(int unfinished, t_dlist **lst)
{
	int		ret;
	char	*line;
	//line = ft_strdup("a;");//
	if (!*lst)
		write(1, "minishell", 9);
	write(1, "> ", 2);
	if ((ret = get_next_line(STDIN_FILENO, &line)) != 0 || *line)
	{
		printf("unfinished=%c\n", unfinished);//
		if (!*lst)
			unfinished = 0;
		if (parse_line(line, lst, unfinished)) //ptr //initialize ptr = lst
		{
			//analise_lst(lst);
			//free_and_exit();
		}
		//else
	}
	if (ret == 0)
	{
		//free(line);
		//free_and_exit(); //if signal
	}
	//free(line);
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
