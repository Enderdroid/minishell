#include "../../include/libincludes.h"

int r_sub_exec(t_exec *exec, int p_fd[2], int *rv)
{
	int pid;

	*rv = 0;
	if (!(pid = fork()))
	{
		if (p_fd[0] != 0)
			dup2(p_fd[0], 0);
		if (p_fd[1] != 1)
			dup2(p_fd[1], 1);
		if (p_fd[0] != 0)
			close(p_fd[0]);
		if (p_fd[1] != 1)
			close(p_fd[1]);
		execve(exec->full_name, exec->argv, g_data->l_env);
		exit(*rv);
	}
	else
		return (-1);
	g_data->pid = pid;
	return (0);
}

int redir_execute(t_exec *exec)
{
	int rv;
	int ret;

	rv = 0;
	//printf("\nREDIR\n");
	//printf("%s -- %s\n", exec->argv[0], exec->argv[1]);
	if (exec->full_name)
		r_sub_exec(exec, exec->fd_new, &rv);
	else
		rv = builtin_call(exec);
	if (exec->fd_new[0] != 0)
		close(exec->fd_new[0]);
	if (exec->fd_new[1] != 1)
		close(exec->fd_new[1]);
	if (exec->full_name)
	{
		waitpid(g_data->pid, &rv, 0);
		g_data->pid = 0;
		ret = WEXITSTATUS(rv);
	}
	else
		ret = rv;
	return (ret);
}
