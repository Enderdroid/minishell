#include "../../include/libbuiltins.h"

int put_unset_err(char *arg)
{
	int i;

	i = 0;
	ft_putstr_fd("bash: export : \'", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (-1);
}

ssize_t		b_unset(char **argv)
{
	t_env *env;
	int	i;

	i = 0;
	while (argv[++i])
	{
		// if (!(is_env(argv[++i])))
			// return (put_unset_err(argv[++i]));
		// else
		// {
			env = find_env_unset(argv[++i]);
			if (env)
				del_env(env);
		// }
	}
	return (0);
}