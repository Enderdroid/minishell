#include "../../include/libbuiltins.h"
#include <dirent.h>

//C_PATH - нынешний путь
//он всегда верен по совместительству является буфером, равным 1024
//N_PATH - аргумент
//скорее всего неправильный

int			cd_errno(t_exec *exec, char *arg)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (!arg)
		ft_putstr_fd(exec->argv[1], 2);
	else
		ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int		cd_not_set(char *key, char *option)
{
	ft_putstr_fd("minishell: cd: ", 2);
	if (key)
	{
		ft_putstr_fd(key, 2);
		ft_putendl_fd(" not set", 2);
		return (1);
	}
	ft_putchar_fd(option[0], 2);
	ft_putchar_fd(option[1], 2);
	ft_putendl_fd(": invalid option", 2);
	return (2);
}

int		env_arg(char *key, t_exec *exec)
{
	int ret;
	t_env *env;

	env = find_env_b(key);
	if (env == NULL)
		return (cd_not_set(key, NULL));
	else if (env->value == NULL)
		return (cd_not_set(key, NULL));
	ret = chdir(env->value);
	if (ret == -1)
		cd_errno(exec, env->value);
	return (0);
}

int do_chdir(char *argv, t_exec *exec)
{
	int ret;

	if (!argv)
		return (env_arg("HOME", exec));
	else if (!ft_strcmp(argv, "-"))
		return (env_arg("OLDPWD", exec));
	else if (argv[0] == '-' && argv[1])
		return (cd_not_set(NULL, argv));
	ret = chdir(argv);
	if (ret == -1)
		cd_errno(exec, argv);
	return (ret);
}

int		b_cd(t_exec *exec)
{
	int		ret;
	char	c_path_buf[PATH_MAX];

	getcwd(c_path_buf, PATH_MAX);
	ret = do_chdir(exec->argv[1], exec);
	if (!ret && !(g_data->pid))
	{
		g_data->u_env->l_old_pwd = change_env_value(g_data->u_env->l_old_pwd, "OLDPWD", c_path_buf, NULL);
		getcwd(c_path_buf, PATH_MAX);
		g_data->u_env->l_pwd = change_env_value(g_data->u_env->l_pwd, "PWD", c_path_buf, NULL);
		remake_lenv();
	}
	if (ret == -1)
		ret = 1;
	return (ret);
}
