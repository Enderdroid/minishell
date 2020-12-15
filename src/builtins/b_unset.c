#include "../../include/libbuiltins.h"

ssize_t		b_unset(t_exec *exec)
{
	t_env *env;
	int	i;
	int code_buf;

	i = 0;
	code_buf = 0;
	while (exec->argv[++i])
	{
		if (is_env(exec->argv[i]) == -1)
		{
			code_buf = 1;
			b_put_error("unset", exec->argv[i], "not a valid identifier", 1);
			continue;
		}
		else if (!(g_data->pid))
		{
			env = find_env_b(exec->argv[i]);
			if (env)
				del_env(env);
		}
	}
	if (exec->argv[1] && g_data->pid)
		remake_lenv();
	//if (!(g_data->pid))
		g_data->code = code_buf;
	return (0);
}