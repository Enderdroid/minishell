#include "../../include/libbuiltins.h"

void put_export_env(int fd)
{
	int ind;
	t_env *var;

	ind = -1;

	while (g_data->env_arr[++ind])
	{
		var = g_data->env_arr[ind];
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(var->key, fd);
		if (var->value)
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(var->value, fd);
			ft_putstr_fd("\"", fd);
		}
		ft_putstr_fd("\n", fd);
	}
}

void parse_export(char *arg, int *code_buf)
{
	int i;
	int ret;
	char **env_buf;
	t_env *c_env;

	i = -1;
	if ((ret = is_env(arg)) == -1)
	{
		*code_buf = 1;
		return (b_put_error("export", arg, "not a valid identifier", 1));
	}
	if (!(env_buf = ft_split(arg, '=')))
		free_and_exit(ERRNO);
	c_env = find_env_unset(env_buf[0]);
	if (c_env && ret == 1)
		change_env_value(c_env, env_buf[1]);
	else if (c_env && ret == 0)
		change_env_value(c_env, NULL);
	else if (!c_env && ret == 1)
		add_env(env_buf[0], env_buf[1]);
	else
		add_env(env_buf[0], NULL);
}

ssize_t	b_export(t_exec *exec)
{
	int i;
	int ret;
	int code_buf;

	code_buf = 0;
	if (!exec->argv[1])
		put_export_env(exec->fd_new[1]);
	i = 0;
	while (exec->argv[++i])
		parse_export(exec->argv[i], &code_buf);
	// if (exec->argv[1])
		// remake_lenv();
	g_data->code = code_buf;
	return (0);
}
