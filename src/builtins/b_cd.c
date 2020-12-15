#include "../../include/libbuiltins.h"
#include <dirent.h>

//C_PATH - нынешний путь
//он всегда верен по совместительству является буфером, равным 1024
//N_PATH - аргумент
//скорее всего неправильный

int			home_arg()
{
	int ret;
	char *key;
	char *home;

	key = ft_strdup("HOME");
	if (!(home = find_env(key)))
		free_and_exit(ERRNO);
	ret = chdir(home);
	free(home);
	return (ret);
}

int			cd_errno(t_exec *exec)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(exec->argv[1], 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

ssize_t		b_cd(t_exec *exec)
{
	int		ret;
	char	c_path_buf[PATH_MAX];

	getcwd(c_path_buf, PATH_MAX);
	if (!exec->argv[1])
		ret = home_arg();
	else
		ret = chdir(exec->argv[1]);

	if (ret != -1)
	{
		if (!(g_data->pid))
		{
			g_data->u_env->l_old_pwd = change_env_value(g_data->u_env->l_old_pwd, "OLDPWD", c_path_buf);
			getcwd(c_path_buf, PATH_MAX);
			g_data->u_env->l_pwd = change_env_value(g_data->u_env->l_pwd, "PWD", c_path_buf);
		}
		g_data->code = 0;
		//printf("g_data->code= %i\n", g_data->code);//
	}
	else
		g_data->code = cd_errno(exec);
	if (!(g_data->pid))
		remake_lenv();
	return (0);
}
