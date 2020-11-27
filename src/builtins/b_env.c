#include "../../include/libbuiltins.h"

void	b_put_env(t_env *var, int fd)
{
	ft_putstr_fd(var->key, fd);
	ft_putstr_fd("=", fd);
	ft_putendl_fd(var->value, fd);
}

int b_env(int fd)
{
	int	ind;

	ind = -1;
	while (g_data->env_arr[++ind])
		if (g_data->env_arr[ind]->value)
			b_put_env(g_data->env_arr[ind], fd);
	return (0);
}
