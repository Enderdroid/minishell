/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:44:22 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/24 20:44:06 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

char	*find_env(char *key)
{
	char	*value;
	int		i;

	if (!key)
		return (NULL);
	i = -1;
	value = NULL;
	//printf("%s\n", (g_data->env_arr)[1]->key);
	while (g_data->env_arr[++i])
	{
		//printf("%s, %i\n", g_data->env_arr[i]->key, i);//
		if (ft_strcmp(g_data->env_arr[i]->key, key) == 0)
		{
			if (g_data->env_arr[i]->value)
			{
				if (!(value = ft_strdup(g_data->env_arr[i]->value)))
					return (NULL);
			}
			break ;
		}
	}
	if (!value)
		value = ft_strdup("");
	free(key);
	return (value);
}

t_env *find_env_unset(char *key)
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

