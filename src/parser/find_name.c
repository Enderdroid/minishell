/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:53:59 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/29 23:19:54 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int	new_len(char *str)
{
	int i;
	int l;
	int change;

	i = -1;
	l = 0;
	change = 1;
	while (str[++i])
	{
		if (i > 0 && str[i - 1] == '/' && str[i] == '/')
			change = 1;
		else
			++l;
	}
	return ((change) ? l : -1);
}

static char	*del_double_slash(char *str)
{
	int		i;
	int		l;
	char	*new;

	if ((l = new_len(str)) == -1)
		return (ft_strdup(str));
	if (!(new = (char *)malloc(sizeof(char) * (l + 1))))
		free_and_exit(ERRNO);
	i = -1;
	l = 0;
	while (str[++i])
	{
		if (!(i > 0 && str[i - 1] == '/' && str[i] == '/'))
			new[l++] = str[i];
	}
	new[l] = '\0';
	//printf("!!%s\n", new);//
	return (new);
}

static void	fill_name_path(char *str, t_exec *exec)
{
	char *s;
	char *str_m;

	str_m = del_double_slash(str);
	s = ft_strrchr(str_m, '/');
	exec->name = (s) ? ft_strdup(s + 1) : ft_strdup(str);
	if (!exec->name)
		free_and_exit(ERRNO);
	if (s)
	{
		exec->path = ft_substr(str_m, 0, s - str_m);
		if (!exec->path)
			free_and_exit(ERRNO);
	}
	free(str_m);
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
