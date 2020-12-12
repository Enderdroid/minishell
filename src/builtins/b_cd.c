#include "../../include/libbuiltins.h"

//C_PATH - нынешний путь
//он всегда верен по совместительству является буфером, равным 1024
//N_PATH - аргумент
//скорее всего неправильный

ssize_t		b_cd(t_exec *exec)
{
	int		ret;
	char	c_path_buf[PATH_MAX];
	char	*c_path;

	getcwd(c_path_buf, PATH_MAX);
	if (!exec->argv[1])
		ret = chdir("~");
	else
		ret = chdir(exec->argv[1]);
	if (ret != -1)
	{
		if (!(c_path = (char *)malloc(ft_strlen(c_path_buf) * sizeof(char))))
			exit_with_errno();
		change_env_value(g_data->u_env->l_old_pwd, c_path);
		change_env_value(g_data->u_env->l_pwd, ft_strdup(exec->argv[1]));
		g_data->code = 0;
	}
	else
		b_put_error("cd", exec->argv[1], "No such file or directory", 1);
	return (0);
}
