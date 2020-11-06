#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../include/libutils.h"

int ft_execute(t_exec *exec)
{
	int f_ret;
	int rv;
	char *f_name;
	f_ret = fork();
	// if (f_ret == -1)
		// ERROR
	if (f_ret == 0)
	{
		if (exec->fd_new[0] > 0)
		{
			//В процессоре считать отсюда в argv
			close(exec->fd_new[0]);
			dup2(exec->fd_new, STDOUT_FILENO);
		}
		f_name = ft_strjoin(exec->path, exec->name);
		// if (!f_name)
			// ERROR
		execve(f_name, exec->argv, exec->env);
		exit(rv);
	}
	wait(0);
	exec->ret = WEXITSTATUS(rv);
	return (rv);
}
