/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/13 19:34:10 by ttamesha         ###   ########.fr       */
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

void	parse_line(char *line, t_dlist **lst, int last_char)
{
	int q_closed;

	q_closed = get_tokens(lst, line, last_char);
	free(line);
	print_list(*lst);//
	validate_tokens(lst, q_closed);
	correct_tokens(lst);
	print_list(*lst);//
	//create struct exec and send
	analise_tokens(lst);
	//free_tokens(lst);
}

void	parse_input(int unfinished, t_dlist **lst)
{
	int		ret;
	char	*line;
	//line = ft_strdup("");//
	if (!*lst)
		write(1, "minishell", 9);
	write(1, "> ", 2);
	if ((ret = get_next_line(STDIN_FILENO, &line)) != 0)
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
		free_data();
		exit(0);
	}
	printf("do I ever get here?");
	//free(line);//freed after split?
}
