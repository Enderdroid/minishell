/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env_unset.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:44:22 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/26 01:41:02 by ttamesha         ###   ########.fr       */
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
		//printf("%s, %i\n", g_data->env_arr[i]->key, i);//
		if (ft_strcmp(g_data->env_arr[i]->key, key) == 0)
			return (g_data->env_arr[i]);
	return (NULL);
}
