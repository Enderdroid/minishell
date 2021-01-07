/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 17:51:43 by tkleiner          #+#    #+#             */
/*   Updated: 2021/01/07 17:51:43 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libstruct.h"
#include "../../include/libincludes.h"

static void	env_free_arr(char **arr, char *key)
{
	if (arr)
		free_arr(arr);
	if (key)
		free(key);
	free_and_exit(ERRNO);
}

static int	get_env_count(void)
{
	int		size;

	size = 0;
	while (g_data->env_arr[size])
		++size;
	return (size);
}

t_env		*add_env(char *key, char *value, char **to_free)
{
	t_env	*env_buf;
	int		old_size;

	old_size = get_env_count();
	env_buf = NULL;
	if ((sub_add_env(old_size)) == -1 ||
	!(env_buf = (t_env *)malloc(sizeof(t_env))))
		env_free_arr(to_free, key);
	if (!(env_buf->key = ft_strdup(key)))
		env_free_arr(to_free, key);
	if (value && !(env_buf->value = ft_strdup(value)))
		env_free_arr(to_free, key);
	else if (!value)
		env_buf->value = NULL;
	g_data->env_arr[old_size] = env_buf;
	return (g_data->env_arr[old_size]);
}

int			del_env(t_env *env)
{
	int		old_size;
	int		ret;

	old_size = get_env_count();
	if ((ret = sub_del_env(old_size, env)) == -1)
		free_and_exit(ERRNO);
	free(env->key);
	free(env->value);
	free(env);
	return (0);
}

t_env		*change_env_value(t_env *env, char *key,
char *value, char **to_free)
{
	char	*val_buf;

	if (env)
	{
		if (value && !(val_buf = ft_strdup(value)))
			env_free_arr(to_free, NULL);
		else if (!value && !(val_buf = ft_strdup("")))
			env_free_arr(to_free, NULL);
		if (env->value)
			free(env->value);
		env->value = val_buf;
	}
	else if (value)
		return (add_env(key, value, to_free));
	else
		return (add_env(key, "", to_free));
	return (env);
}
