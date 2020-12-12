#include "../../include/libbuiltins.h"

ssize_t b_pwd(t_exec *exec)
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_putstr_fd(path, exec->fd_new[1]);
	g_data->code = 0;
	return (0);
}
