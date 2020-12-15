#include "../../include/libstruct.h"
#include "../../include/libincludes.h"

int			get_env_count()
{
	int		size;

	size = 0;
	while (g_data->env_arr[size])
		++size;
	return (size);
}

t_env		*add_env(char *key, char *value)
{
	t_env	*env;
	int		old_size;

	old_size = get_env_count();
	if ((realloc_env((old_size + 1), old_size)) == -1  ||
		!(env = (t_env *)malloc(sizeof(t_env))))
	{
			free(key);
			if (value)
				free(value);
			free_and_exit(ERRNO);
	}
	env->key = key;
	env->value = value;
	g_data->env_arr[old_size] = env;
	return (g_data->env_arr[old_size]);
}

int			del_env(t_env *env)
{
	int		old_size;
	int		ret;

	old_size = get_env_count();
	if ((ret = realloc_env((old_size - 1), old_size)) == -1)
		free_and_exit(ERRNO);
	free(env->key);
	free(env->value);
	free(env);
	return (0);
}

t_env		*change_env_value(t_env *env, char *key, char *value)
{
	char *val_buf;
	char *key_buf;

	if (value)
		if (!(val_buf = ft_strdup(value)))
			free_and_exit(ERRNO);
	if (key && !env)
		if (!(key_buf = ft_strdup(key)))
		{
			if (value)
				free(val_buf);
			free_and_exit(ERRNO);
		}
	if (env)
	{
		free(env->value);
		env->value = val_buf;
	}
	else
		return(add_env(key_buf, val_buf));
	return (env);
}
