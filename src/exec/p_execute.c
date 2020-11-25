#include "../../include/libincludes.h"

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
		printf("\n fdnew == %i\n", exec->fd_new[0]);
		if (exec->fd_new[0] > 0)
		{
			//В процессоре считать отсюда в argv
			close(exec->fd_new[0]);
			dup2(exec->fd_new[0], STDOUT_FILENO);
		}
		f_name = ft_strjoin(exec->path, exec->name);
		// if (!f_name)
			// ERROR
		printf("\n%s -- %s\n", f_name, exec->argv[0]);
		execve(f_name, exec->argv, exec->env);
		exit(rv);
	}
	g_data->pid = f_ret;
	// printf("PID == %i\n", f_ret);
	wait(0);
	g_data->pid = 0;
	exec->ret = WEXITSTATUS(rv);
	return (rv);
}
