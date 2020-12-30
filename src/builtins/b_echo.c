#include "../../include/libbuiltins.h"

int	b_echo(t_exec *exec)
{
	int ind;
	int flag;

	//printf("argv == %s -- %s\n", exec->argv[0], exec->argv[1]);

	flag = 0;
	ind = 0;
	while (exec->argv[++ind] && !(ft_strcmp(exec->argv[ind], "-n")))
		flag = 1;
	while (exec->argv[ind])
	{
		ft_putstr_fd(exec->argv[ind], exec->fd_new[1]);
		++ind;
	}
	if (!flag)
		ft_putstr_fd("\n", exec->fd_new[1]);
	return (0);
}
