/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:53:59 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/12 16:26:18 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void	fill_name_path(char *str, t_exec *exec)
{
	char *s;

	s = ft_strrchr(str, '/');
	exec->name = (s) ? ft_strdup(s + 1) : ft_strdup(str);
	if (!exec->name)
		free_and_exit(ERRNO);
	if (s)
	{
		exec->path = ft_substr(str, 0, s - str);
		if (!exec->path)
			free_and_exit(ERRNO);
	}
	if (exec->path)
	{
		if (!(exec->full_name = ft_strdup(str)))
			free_and_exit(ERRNO);
	}
	//printf("]path=%s\n", exec->path);
}

void		find_name(t_dlist **lptr, t_exec *exec, char **arg)
{
	while (*lptr && ((t_token *)(*lptr)->content)->len == 0)
		*lptr = (*lptr)->next;
	if (*lptr && ((t_token *)(*lptr)->content)->len > 0)
	{
		fill_name_path(((t_token *)(*lptr)->content)->str, exec);
		if (!(*arg = ft_strdup(exec->name)))
			free_and_exit(ERRNO);

		//printf("name = %s\n", exec->name);//
		//printf("path = %s\n", exec->path);//
/*
		printf("head name = %s\n", g_data->exec->name);//
		if (g_data->exec->pipe_to)
			printf("next name = %s\n", ((t_exec *)(g_data->exec->pipe_to))->name);//
		printf("head path = %s\n", g_data->exec->path);*/
		(*lptr) = (*lptr)->next;
	}
}
