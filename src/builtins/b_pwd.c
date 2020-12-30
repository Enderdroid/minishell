#include "../../include/libbuiltins.h"

int b_pwd(t_exec *exec)
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_putendl_fd(path, exec->fd_new[1]);
	return (0);
}
