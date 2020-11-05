/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/06 02:00:04 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

char	*tokenize(t_token *token)
{
	char	*res;
	int		i;
	int		q;

	i = 0;
	q = 0;
	res = malloc(sizeof(char) * (token->len + 1));
	//if (!res) //ERROR
	while(i < token->len)
	{
		if (token->str[i] == '\"')
		{
			res[i] = '0';
			q = (q) ? 0 : 1;
		}
		else if (token->str[i] == '\'' && !q)
		{
			res[i] = '0';
			while (token->str[++i] && token->str[i] != '\'')
				res[i] = '1';
			if (token->str[i])
				res[i] = '0';
		}
		else if (token->str[i] == '\\' && (!q || ft_strchr("$\"\\\0", token->str[i + 1])))
		{
			res[i] = '0';
			if (token->str[++i])
				res[i] = '1';
		}
		else if (token->str[i] == '$' && !ft_strchr(" ~:/.,^+=\\\%\0", token->str[i + 1]) \
										&& !(token->str[i + 1] == '\"' && q))
			res[i] = '2';
		else
			res[i] = '1';
		++i;
	}
	res[token->len] = '\0';
	return (res);
}

void	tokenize_lst(t_dlist **lst, t_env *env)
{
	t_dlist	*ptr;
	char	*res;

	ptr = *lst;
	while(ptr)
	{
		if (((t_token *)(ptr->content))->len > 0)
		{
			res = tokenize((t_token *)(ptr->content));
			printf("%s\n", res);//
			correct_str(&(((t_token *)(ptr->content))->str), ((t_token *)(ptr->content))->len, res);
			printf("%s\n", ((t_token *)(ptr->content))->str);
		}
		ptr = ptr->next;
	}
}

int	parse_line(char *line, t_env *env, t_dlist **lst)
{
//	if (input_is_valid(line)) //do it via list after parsing
	{
		split_line(line, lst);
		//validate(lst); synt err unclosed q ask for input for backslash at the end
		tokenize_lst(lst, env);

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
