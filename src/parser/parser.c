/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/11 00:35:44 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

void	correct_tokens(t_dlist **lst)
{
	t_dlist	*ptr;
	char	*tmp;

	ptr = *lst;
	while (ptr)
	{
		if (((t_token *)(ptr->content))->len > 0)
		{
			tmp = corrected_str(lst, (t_token *)(ptr->content));
			if (tmp)
			{
				free(((t_token *)(ptr->content))->str);
				((t_token *)(ptr->content))->str = tmp;
				((t_token *)(ptr->content))->len = ft_strlen(tmp);
			}
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
	validate_tokens(lst, q_closed);
	correct_tokens(lst);
	print_list(*lst);//

	//create struct exec
	analise_tokens(lst);
	//free_tokens(lst);
	return (1);
}

void	parse_input(int unfinished, t_dlist **lst)
{
	int		ret;
	char	*line;
	//line = ft_strdup("cd | $T");//
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
	//free(line);//freed after split?
}
