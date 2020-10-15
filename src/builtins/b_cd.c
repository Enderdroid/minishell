#include "../../include/libbuiltins.h"
#include "../../include/libutils.h"
#include <sys/syslimits.h>

//C_PATH - нынешний путь
//он всегда верен по совместительству является буфером, равным 1024
//N_PATH - аргумент
//скорее всего неправильный

int		ft_prep_step(char *c_path, char *n_path, int ind)
{
	if (n_path[0] == '.')
	{
		if (n_path[1] == '.' && n_path[2] == '/')
		{
			rm_folder(c_path);
			ind = ft_dellchar(n_path, "123");
		}
		else if (n_path[1] == '/')
			ind = ft_dellchar(n_path, "12");
		return;
	}
	ind = add_folder(c_path, n_path);
}

char	*b_cd(char *c_path, const char *n_path)
{
	int		dot_shift;
	char	*buf_path[2];
	size_t	ind;

	buf_path[0] = ft_strdup(c_path);
	buf_path[1] = ft_strdup(n_path);
	dot_shift = 0;
	ind = 0;
	while (n_path[ind])
		ind += ft_prep_step(buf_path[0], buf_path[1], ind);
	//MY CODE HERE
	return (n_path);
}
