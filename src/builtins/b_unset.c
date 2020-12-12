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
		else
		{
			env = find_env_unset(exec->argv[i]);
			if (env)
				del_env(env);
		}
	}
	// if (exec->argv[1])
		// remake_lenv();
	g_data->code = code_buf;
	return (0);
}