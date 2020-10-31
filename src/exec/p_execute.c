#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int		path_execute(char **path_val, char **p_argv, char **p_env)
{
	char *path;
	int		ret;

	path = s_in_path(path_val, p_argv[0]);
	ret = ft_execute(path, p_argv, p_env);
	return (ret);
}

int		ft_execute(char *path, char **p_argv, char **p_env)
{
	int f_ret;
	int rv;
	char *f_name;

	f_ret = fork();
	// if (f_ret == -1)
		// ERROR
	if (f_ret == 0)
	{
		f_name = ft_strjoin(path, p_argv[0]);
		execve(f_name, p_argv, p_env);
		exit(rv);
	}
	wait(0);
	rv = WEXITSTATUS(rv);
	return (rv);
}
