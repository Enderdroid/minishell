#include "../../include/parser.h"

void	free_data(void)
{
	int i;

	i = -1;
	while(data->env_arr[++i].key)
	{
		free(data->env_arr[i].key);
		free(data->env_arr[i].value);
	}
	if (data->u_env->path_content)
		free(data->u_env->path_content);
	free(data->env_arr);
	free(data->u_env);
	free(data);
}

/*void	free_data(void)
{
	int i;

	i = -1;
	while(data->env_arr[++i]->key)
	{
		free(data->env_arr[i]->key);
		free(data->env_arr[i]->value);
	}
	if (data->u_env->path_content)
		free(data->u_env->path_content);
	free(data->env_arr);
	free(data->u_env);
	free(data);
}*/