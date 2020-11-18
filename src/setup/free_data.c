/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:51:57 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/19 02:16:13 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

void	free_exec(t_exec *exec)
{
	//printf("exec->name: %s\n", exec->name);
	if (exec->name)
		free(exec->name);
	if (exec->path)
		free(exec->path);
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
		free(g_data->env_arr[i]->value);
		free(g_data->env_arr[i]);
	}
	free(g_data->env_arr);
	if (g_data->u_env->path_content)
		free_arr(g_data->u_env->path_content);
	if (g_data->u_env)
		free(g_data->u_env);
	if (g_data->exec)
		free_exec(g_data->exec);
	free(g_data);
}
