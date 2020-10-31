#include "../../include/libbuiltins.h"
#include "../../include/libutils.h"

ssize_t b_env(char **env)
{
	size_t	ind;

	ind = 0;
	while (env[ind])
		ft_putstr_fd(env[ind], 1);
}