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

int			add_env(char *key, char *value)
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
	return (0);
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

int			change_env_value(t_env *env, char *value)
{
	free(env->value);
	env->value = NULL;
	if (value && !(env->value = ft_strdup(value)))
		exit_with_errno();
	return (0);
}
