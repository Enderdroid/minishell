#include "../../include/parser.h"

void	free_env(t_env *env)
{
	int i;

	i = -1;
	while(env[++i].key)
	{
		free(env[i].key);
		free(env[i].value);
	}
	free(env);
}

void	free_path_env(t_u_env *path_env)
{
	if (path_env->path_content)
		free(path_env->path_content);
}