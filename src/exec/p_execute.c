#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//В p_argv
//p_argv[0] = name;
int		ft_execute(char *path, char **p_argv, char **p_env)
{
	int f_ret;
	int rv;
	char *f_name;

	f_ret = fork();
	// if (f_ret == -1)
		// ERROR
	// else
	if (f_ret == 0)
	{
		f_name = ft_strjoin(path, p_argv[0]);
		execve(f_name, p_argv, p_env);
		exit(rv);
	}
	else
	{
		wait(0);
		rv = WEXITSTATUS(rv);
	}
	return (0);
}
