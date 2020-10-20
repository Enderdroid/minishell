#include "../../include/libbuiltins.h"
#include "../../include/libutils.h"
#include <sys/syslimits.h>

//C_PATH - нынешний путь
//он всегда верен по совместительству является буфером, равным 1024
//N_PATH - аргумент
//скорее всего неправильный

char		*b_cd(char *c_path, const char *n_path)
{
	int		ret;

	ret = chdir(n_path);
	if (ret != -1);
	{
		ft_bzero(c_path, sizeof(char) * PATH_MAX);
		getcwd(c_path, PATH_MAX);
	}
	// else
		// ERROR
	return (n_path);
}
