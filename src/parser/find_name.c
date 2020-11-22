/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:53:59 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/21 21:48:38 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	fill_name_path(char *str, t_exec *exec, t_dlist **lst)
{
	char *s;

	if (*(str + 1) == '/')
	{
		if (*str == '.')
			if (!(exec->path = find_env(ft_strdup("PWD"))))
				parser_exit(lst, NULL);
	}
	s = ft_strrchr(str, '/');
	exec->name = (s) ? ft_strdup((s + 1)) : ft_strdup(str);
	if (!exec->name)
		parser_exit(lst, NULL);
	if (s)
	{
		if (exec->path)
			stradd(&(exec->path), ft_substr(str, 1, s - str));
		else
			exec->path = ft_substr(str, 0, s - str);
		if (!exec->path)
			parser_exit(lst, NULL);
	}
}

void		find_name(t_dlist **lst, t_dlist **lptr, t_exec *exec, char **arg)
{
	while (*lptr && ((t_token *)(*lptr)->content)->len == 0)
		*lptr = (*lptr)->next;
	if (*lptr && ((t_token *)(*lptr)->content)->len > 0)
	{
		fill_name_path(((t_token *)(*lptr)->content)->str, exec, lst);
		if (!(*arg = ft_strdup(exec->name)))
			parser_exit(lst, NULL);

		printf("name = %s\n", exec->name);//
		printf("path = %s\n", exec->path);//
/*
		printf("head name = %s\n", g_data->exec->name);//
		if (g_data->exec->pipe_to)
			printf("next name = %s\n", ((t_exec *)(g_data->exec->pipe_to))->name);//
		printf("head path = %s\n", g_data->exec->path);*/
		(*lptr) = (*lptr)->next;
	}
}