#include "../../include/libincludes.h"

ssize_t builtin_call(t_exec *exec)
{
	if (!(ft_strcmp(exec->name, "cd")))
		return (b_cd(exec));
	else if (!(ft_strcmp(exec->name, "echo")))
		return (b_echo(exec));
	else if (!(ft_strcmp(exec->name, "env")))
		return (b_env(exec));
	else if (!(ft_strcmp(exec->name, "exit")))
		return (b_exit(exec));
	else if (!(ft_strcmp(exec->name, "export")))
		return (b_export(exec));
	else if (!(ft_strcmp(exec->name, "pwd")))
		return (b_pwd(exec));
	else if (!(ft_strcmp(exec->name, "unset")))
		return (b_unset(exec));
	else
		return (-1);
}

int sub_exec(t_exec *exec, int *p_fd, int fd, int *rv)
{
	int pid;

	if (exec->full_name)
	{
		if (!(pid = fork()))
		{
			if (p_fd)
			{
				dup2(p_fd[fd], fd);
				close(p_fd[0]);
				close(p_fd[1]);
			}
			execve(exec->full_name, exec->argv, g_data->l_env);
			exit(*rv);
		}
		g_data->pid = pid;
		return (0);
	}
	return (1);
}

int ft_execute(t_exec *exec)
{
	int rv;
	int ret;

	// printf("%s -- %s\n", exec->argv[0], exec->argv[1]);
	rv = 0;
	if (sub_exec(exec, NULL, 0, &rv))
		rv = builtin_call(exec);
	if (exec->full_name)
	{
		waitpid(g_data->pid, &rv, 0);
		g_data->pid = 0;
		ret = WEXITSTATUS(rv);
		// printf ("RET = %i\n", ret);
	}
	else
		ret = rv;
	return (ret);
}
