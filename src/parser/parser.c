/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/18 15:43:24 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"
#include "../../include/lexer.h"

void	correct_tokens(t_dlist **lst)
{
	t_dlist	*lptr;
	char	*newstr;

	lptr = *lst;
	while (lptr)
	{
		if (((t_token *)(lptr->content))->len > 0)
		{
			newstr = corrected_str(lst, (t_token *)(lptr->content));
			//printf("newstr%s\n", newstr);//
			if (newstr)
			{
				if (!ft_strcmp(newstr, "\0") &&
					!(ft_strchr(((t_token *)(lptr->content))->str, '\'') || \
					ft_strchr(((t_token *)(lptr->content))->str, '\"')))
					((t_token *)(lptr->content))->len = 0;
				else
					((t_token *)(lptr->content))->len = 1;
				if (((t_token *)(lptr->content))->len)
				{
					free(((t_token *)(lptr->content))->str);
					((t_token *)(lptr->content))->str = newstr;
				}
				//((t_token *)(lptr->content))->len = ft_strlen(newstr);
			}
			//printf("%s\n", ((t_token *)(lptr->content))->str);//
		}
		lptr = lptr->next;
	}
}

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
		//if (exec)
			//ft_processor(data->exec);
	}
	parse_input(0, lst);
}

void	parse_line(char *line, t_dlist **lst, int last_char)
{
	int q_closed;

	q_closed = get_tokens(lst, line, last_char);
	free(line);
	print_list(*lst);//
	validate_tokens(lst, q_closed);
	correct_tokens(lst);
	print_list(*lst);//
	analise_tokens(lst);
}

void	parse_input(int unfinished, t_dlist **lst)
{
	int		ret;
	char	*line;
	//line = ft_strdup("$AAA "" $AA''");//
	if (!*lst)
		write(1, "minishell", 9);
	write(1, "> ", 2);
	if ((ret = get_next_line(&line)) != 0)
	{//printf("gnl=%i\n", ret);//
		printf("unfinished=%c\n", unfinished);//
		if (!*lst)
			unfinished = 0;
		parse_line(line, lst, unfinished);
	}
	if (ret == 0)
	{
		//printf("gnl=%i\n", ret);
		free(line);
		write(1, "exit\n", 5);
		free_and_exit(0);
	}
	printf("do I ever get here?");//
	//free(line);//freed after split?
}
