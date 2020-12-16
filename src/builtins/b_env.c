#include "../../include/libbuiltins.h"

void	b_put_env(t_env *var, int fd)
{
	ft_putstr_fd(var->key, fd);
	ft_putstr_fd("=", fd);
	ft_putendl_fd(var->value, fd);
}

ssize_t b_env(t_exec *exec)
{
	int	ind;

	ind = -1;
	while (g_data->env_arr[++ind])
		if (g_data->env_arr[ind]->value)
			b_put_env(g_data->env_arr[ind], exec->fd_new[1]);
	return (0);
}