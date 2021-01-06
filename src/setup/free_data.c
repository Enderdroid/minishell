/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:57 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/06 19:06:46 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	free_tokens(t_dlist **lst)
{
	t_dlist *tmp;
	t_dlist *lptr;

	if (!lst || !*lst)
		return ;
	lptr = *lst;
	while (lptr)
	{
		tmp = lptr->next;
		//printf("str to free: %s\n", ((t_token *)(lptr->content))->str);
		if (((t_token *)(lptr->content))->str)
		{
			free(((t_token *)(lptr->content))->str);
			((t_token *)(lptr->content))->str = NULL;
		}
		free((t_token *)(lptr->content));
		free(lptr);
		lptr = tmp;
	}
	*lst = NULL;
}

void	free_exec(t_exec *exec)
{
	if (exec->name)
		free(exec->name);
	if (exec->path)
		free(exec->path);
	if (exec->full_name)
		free(exec->full_name);
	if (exec->argv)
		free_arr(exec->argv);
	if (exec->pipe_to)
		free_exec(exec->pipe_to);
	if (exec->fd_new[0] > 1)
		close(exec->fd_new[0]);
	if (exec->fd_new[1] > 1)
		close(exec->fd_new[1]);
	free(exec);
}

void	free_data(void)
{
	int i;

	i = -1;
	while(g_data->env_arr[++i])
	{
		free(g_data->env_arr[i]->key);
		g_data->env_arr[i]->key = NULL;
		if (g_data->env_arr[i]->value)
		{
			free(g_data->env_arr[i]->value);
			g_data->env_arr[i]->value = NULL;
		}
		free(g_data->env_arr[i]);
		g_data->env_arr[i] = NULL;
	}
	free(g_data->env_arr);
	g_data->env_arr = NULL;
	if (g_data->u_env)
	{
		if (g_data->u_env->path_content)
		{
			free_arr(g_data->u_env->path_content);
			g_data->u_env->path_content = NULL;
		}
		if (g_data->u_env->home)
			free(g_data->u_env->home);
		free(g_data->u_env);
		g_data->u_env = NULL;
	}
	if (g_data->l_env)
	{
		free_arr(g_data->l_env);
		g_data->l_env = NULL;
	}
	if (g_data->exec)
	{
		free_exec(g_data->exec);
		g_data->exec = NULL;
	}
	if (g_data->lst)
	{
		free_tokens(&(g_data->lst));
		g_data->lst = NULL;
	}
	free(g_data);
	g_data = NULL;
}

/*
void	free_data(void)
{
	int i;

	i = -1;
	while(g_data->env_arr[++i])
	{
		free(g_data->env_arr[i]->key);
		if (g_data->env_arr[i]->value)
			free(g_data->env_arr[i]->value);
		free(g_data->env_arr[i]);
	}
	free(g_data->env_arr);
	if (g_data->u_env)
	{
		if (g_data->u_env->path_content)
			free_arr(g_data->u_env->path_content);
		if (g_data->u_env->home)
			free(g_data->u_env->home);
		free(g_data->u_env);
	}
	if (g_data->l_env)
		free_arr(g_data->l_env);
	if (g_data->exec)
		free_exec(g_data->exec);
	if (g_data->lst)
		free_tokens(&(g_data->lst));
	free(g_data);
}
*/