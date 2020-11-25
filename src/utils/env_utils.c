#include "../../include/libstruct.h"
#include "../../include/libincludes.h"

int get_env_count()
{
	int size;

	size = 0;
	while (g_data->env_arr[size])
		++size;
	return (size);
}

int add_env(char *key, char *value)
{
	t_env *env;
	int		old_size;

	old_size = get_env_count();
	env = (t_env *)malloc(sizeof(t_env));
	env->key = key;
	env->value = value;
	realloc_env((old_size + 1), old_size);
	g_data->env_arr[old_size] = env;
}

int del_env(t_env *env)
{
	int old_size;

	old_size = get_env_count();
	free(env->key);
	free(env->value);
	env = NULL;
	realloc_env((old_size - 1), old_size);
	free(env);
	return (0);
}

int change_env_value(t_env *env, const char *value)
{
	free(env->value);
	env->value = ft_strdup(value);
	return (0);
}