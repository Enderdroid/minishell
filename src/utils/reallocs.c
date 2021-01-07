/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reallocs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:55 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:55 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libincludes.h"
#include "../../include/libstruct.h"

int			sub_add_env(int old_size)
{
	t_env	**new_arr;
	int		i;

	i = -1;
	if (!(new_arr = (t_env**)malloc(sizeof(t_env*) * (old_size + 2))))
		return (-1);
	while (++i <= old_size)
		new_arr[i] = g_data->env_arr[i];
	new_arr[old_size + 1] = NULL;
	free(g_data->env_arr);
	g_data->env_arr = new_arr;
	return (0);
}

int			sub_del_env(int old_size, t_env *env)
{
	t_env	**new_arr;
	int		i;
	int		j;

	i = 0;
	j = -1;
	if (!(new_arr = (t_env**)malloc(sizeof(t_env*) * (old_size))))
		return (-1);
	while (i <= old_size)
	{
		if (g_data->env_arr[i] != env)
			new_arr[++j] = g_data->env_arr[i];
		++i;
	}
	new_arr[old_size - 1] = NULL;
	free(g_data->env_arr);
	g_data->env_arr = new_arr;
	return (0);
}
