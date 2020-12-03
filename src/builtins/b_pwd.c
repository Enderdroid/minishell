#include "../../include/libbuiltins.h"

int		b_pwd(int fd)
{
	char path[PATH_MAX];

	getcwd(path, PATH_MAX);
	ft_putstr_fd(path, fd);
	return (0);
}
