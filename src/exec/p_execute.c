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
		return (b_exit());
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

	rv = 0;
	if (sub_exec(exec, NULL, 0, &rv))
		rv = builtin_call(exec);
	if (exec->full_name)
	{
		wait(0);
		g_data->pid = 0;
		ret = WEXITSTATUS(rv);
	}
	else
		ret = rv;
	return (ret);
}

int redir_execute(t_exec *exec)
{
	int rv;
	int ret;

	rv = 0;
	if (sub_exec(exec, exec->fd_new, 1, &rv))
		rv = builtin_call(exec);
	if (exec->fd_new[0] != 0)
		close(exec->fd_new[0]);
	if (exec->fd_new[1] != 1)
		close(exec->fd_new[1]);
	if (exec->full_name)
	{
		wait(0);
		g_data->pid = 0;
		ret = WEXITSTATUS(rv);
	}
	else
		ret = rv;
	return (ret);
}

int pipe_b_exec(t_exec *exec, int *rv)
{
	int pid;

	if (!(pid = fork()))
	{
		*rv = builtin_call(exec);
		exit(*rv);
	}
	g_data->pid = pid;
	return (0);
}

int p_redir_execute(t_exec *exec)
{
	int rv;
	int ret;

	rv = 0;
	if (sub_exec(exec, exec->fd_new, 1, &rv))
		pipe_b_exec(exec, &rv);
	if (exec->fd_new[0] != 0)
		close(exec->fd_new[0]);
	if (exec->fd_new[1] != 1)
		close(exec->fd_new[1]);
	wait(0);
	g_data->pid = 0;
	ret = WEXITSTATUS(rv);
	return (ret);
}

int			ft_pipe_part(t_exec *exec, int *p_fd, int fd)
{
	int		rv;
	int		ret;

	rv = 0;
	if (exec->fd_new[0] != 0 || exec->fd_new[1] != 1)
		return (p_redir_execute(exec));
	if ((ret = sub_exec(exec, p_fd, fd, &rv)))
			pipe_b_exec(exec, &rv);
	return (WEXITSTATUS(rv));
}

int ft_pipe(t_exec *pipe_list)
{
	int p_fd_new[2];

	while (pipe_list->pipe_to)
	{
		pipe(p_fd_new);
		if (pipe_list->name)
		{
			pipe_list->ret = ft_pipe_part(pipe_list, p_fd_new, 1);
			wait(0);
		}
		g_data->pid = 0;
		g_data->code = pipe_list->ret;
		if (pipe_list->pipe_to->name)
			pipe_list->pipe_to->ret = ft_pipe_part(pipe_list->pipe_to, p_fd_new, 0);
		close(p_fd_new[0]);
		close(p_fd_new[1]);
		if (pipe_list->pipe_to->name)
			wait(0);
		g_data->pid = 0;
		g_data->code = pipe_list->pipe_to->ret;
		pipe_list = pipe_list->pipe_to;
	}
	return (0);
}
