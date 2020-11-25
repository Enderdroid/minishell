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
		if (var->value[0])
		{
			ft_putstr_fd("=", fd);
			ft_putstr_fd("\"", fd);
			ft_putstr_fd(var->value, fd);
			ft_putendl_fd("\"", fd);
		}
		else
			ft_putstr_fd("\n", fd);
	}
}

int put_export_err(char *arg)
{
	int i;

	i = 0;
	ft_putstr_fd("bash: export : \'", 2);
	while (arg[i] != '=')
		++i;
	write(2, arg, i);
	ft_putendl_fd("\': not a valid identifier", 2);
	return (0);
}

	int parse_export(char *arg)
{
	int i;
	char **key_value;

	i = -1;
	while (arg[++i] && arg[i] != '=')
		if (arg[i] == ' ')
			return (put_export_err(arg));
	if (arg[i] != '=')
		add_env(arg, NULL);
	else if (!arg[i + 1])
		add_env(arg, strdup(""));
	else
	{
		key_value = ft_split(arg, '=');
		add_env(key_value[0], key_value[1]);
	}
	return (0);
}

ssize_t	b_export(char **argv, int fd)
{
	int i;
	int ret;
	char **key_value;

	if (!argv[1])
		put_export_env(fd);
	i = 0;
	while (argv[++i])
		parse_export(argv[i]);
	return (0);
}
