/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remake_lenv.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:58 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:58 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libstruct.h"
#include "../../include/libincludes.h"

static int	get_lenv_size(void)
{
	int		size;
	int		ind;

	ind = -1;
	size = 0;
	while (g_data->env_arr[++ind])
		if (g_data->env_arr[ind]->value)
			++size;
	return (size);
}

static void	exit_from_lenv(char ***l_env)
{
	int		ind;

	ind = -1;
	while (*l_env[++ind])
		free(*l_env[++ind]);
	free(*l_env);
	free_and_exit(ERRNO);
}

static int	fill_lenv(int new_size, char **new_lenv)
{
	int		ind;
	int		filled_ind;
	char	*val_buf;

	ind = -1;
	filled_ind = 0;
	while (g_data->env_arr[++ind] && filled_ind < new_size)
		if (g_data->env_arr[ind]->value)
		{
			if (!(val_buf = ft_strjoin(g_data->env_arr[ind]->key, "=")))
				return (-1);
			if (!(new_lenv[filled_ind] =
			ft_strjoin(val_buf, g_data->env_arr[ind]->value)))
			{
				free(val_buf);
				return (-1);
			}
			free(val_buf);
			++filled_ind;
		}
	return (0);
}

void		remake_lenv(void)
{
	char	**new_lenv;
	int		new_size;
	int		ind;
	int		ret;

	ind = -1;
	new_size = get_lenv_size();
	if (!(new_lenv = (char**)malloc(sizeof(char*) * (new_size + 1))))
		free_and_exit(ERRNO);
	new_lenv[new_size] = NULL;
	ret = fill_lenv(new_size, new_lenv);
	if (ret == -1)
		exit_from_lenv(&new_lenv);
	else
	{
		while (g_data->l_env[++ind])
			free(g_data->l_env[ind]);
		free(g_data->l_env);
	}
	g_data->l_env = new_lenv;
}
