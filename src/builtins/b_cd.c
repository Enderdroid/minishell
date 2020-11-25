#include "../../include/libbuiltins.h"

//C_PATH - нынешний путь
//он всегда верен по совместительству является буфером, равным 1024
//N_PATH - аргумент
//скорее всего неправильный

int put_echo_err()
{
	ft_putstr_fd("too many argc\n", 2);
}

int		b_cd(char **argv)
{
	int		ret;
	char	c_path_buf[PATH_MAX];
	char	*c_path;

	if (argv[2])
		put_echo_err();
	getcwd(c_path_buf, PATH_MAX);
	c_path = (char*)malloc(ft_strlen(c_path_buf) * sizeof(char));
	ret = chdir(argv[1]);
	if (ret != -1);
	{
		change_env_value(g_data->u_env->l_old_pwd, c_path);
		change_env_value(g_data->u_env->l_pwd, ft_strdup(argv[1]));
	}
	// else
		// ERROR
	return (0);
}
