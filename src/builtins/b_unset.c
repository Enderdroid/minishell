#include "../../include/libbuiltins.h"

int		b_unset(t_exec *exec)
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
			printf("\n\nSEARCHING\n\n");
			env = find_env_b(exec->argv[i]);
			printf("\n\nFOUND\n\n");
			if (env)
				del_env(env);
			printf("\n\nDELETED\n\n");
		}
	}
	printf("\n\nENDED\n\n");
	if (exec->argv[1] && g_data->pid)
		remake_lenv();
	return (code_buf);
}
