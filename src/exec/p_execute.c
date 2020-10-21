#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

//В p_argv
//p_argv[0] = name;
int		ft_execute(char *name, char **p_argv, char **p_env)
{
	int f_ret;
	int rv = 100;
	f_ret = fork();
	// if (f_ret == -1)
		// ERROR
	// else
	if (f_ret == 0)
	{
		execve(name, p_argv, p_env);
		exit(rv);
	}
	else
	{
		wait ();
		printf("RV = %i\n", WEXITSTATUS(rv));
	}
	return (0);
}
