/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:44:22 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/30 22:18:44 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libstruct.h"

t_env	*find_env_b(char *key)
{
	int i;

	if (!key)
		return (NULL);
	i = -1;
	//printf("%s\n", (g_data->env_arr)[1]->key);
	while (g_data->env_arr[++i])
	{
		//printf("\n%i -- %s\n", i, g_data->env_arr[i]->key);
		//printf("%s, %i\n", g_data->env_arr[i]->key, i);//
		if (ft_strcmp(g_data->env_arr[i]->key, key) == 0)
			return (g_data->env_arr[i]);
	}
	return (NULL);
}
