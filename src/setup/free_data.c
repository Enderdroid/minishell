#include "../../include/parser.h"

void	free_exec(t_exec *exec)
{
	if (exec->name)
		free(exec->name);
	if (exec->path)
		free(exec->path);
	if (exec->argv)
		free_arr(exec->argv);
	if (exec->pipe_to)
		free_exec(exec->pipe_to);
	if (exec->fd_new[0] > 1)
		close(exec->fd_new[0]);
	if (exec->fd_new[1] > 1)
		close(exec->fd_new[1]);
}

void	free_data(void)
{
	int i;

	i = -1;
	while(data->env_arr[++i])
	{
		free(data->env_arr[i]->key);
		free(data->env_arr[i]->value);
		free(data->env_arr[i]);
	}
	free(data->env_arr);
	if (data->u_env->path_content)
		free_arr(data->u_env->path_content);
	if (data->u_env)
		free(data->u_env);
	if (data->exec)
		free_exec(data->exec);
	free(data);
}
