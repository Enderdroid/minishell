#include "../../include/libincludes.h"

int builtin_call(t_exec *exec)
{
	if (!(ft_strcmp(exec->name, "cd")))
		return (b_cd(exec->argv));
	else if (!(ft_strcmp(exec->name, "echo")))
		return (b_echo(exec->argv));
	else if (!(ft_strcmp(exec->name, "env")))
		return (b_env(1));
	// if (!(ft_strcmp(exec->name, "exit")))
	// ret = b_exit();
	else if (!(ft_strcmp(exec->name, "export")))
		return (b_export(exec->argv));
	else if (!(ft_strcmp(exec->name, "pwd")))
		return (b_pwd(1));
	else if (!(ft_strcmp(exec->name, "unset")))
		return (b_unset(exec->argv));
	else
		return (-1);
}

void pipe_env(t_exec *exec, int *p_fd, int fd, int rv)
{
	char *f_name;

	if (p_fd)
	{
		dup2(p_fd[fd], fd);
		if (exec->fd_new[0] != 0)
			close(p_fd[0]);
		if (exec->fd_new[1] != 1)
			close(p_fd[1]);
	}
	if (exec->full_name)
		execve(exec->full_name, exec->argv, exec->env);
	else
		builtin_call(exec);
	exit(rv);
}

int			ft_pipe_part(t_exec *exec, int *p_fd, int fd)
{
	int		pid;
	int		rv;

	rv = 0;
	//exec->full_name = ft_strjoin(exec->path, exec->name);
	if (!(pid = fork()))
		pipe_env(exec, p_fd, fd, rv);
	g_data->pid = pid;
	if (fd == 0)
		close(p_fd[0]);
	if (fd == 0)
		close(p_fd[1]);
	wait(0);
	g_data->pid = 0;
	if (exec->full_name)
		exec->ret = WEXITSTATUS(rv);
	else
		exec->ret = rv;
	return (exec->ret);
}

int			ft_execute(t_exec *exec)
{
	int		pid;
	int		rv;

	rv = 0;
	//exec->full_name = ft_strjoin(exec->path, exec->name);
	if (!(pid = fork()))
		pipe_env(exec, NULL, 0, rv);
	g_data->pid = pid;
	wait(0);
	g_data->pid = 0;
	if (exec->full_name)
		exec->ret = WEXITSTATUS(rv);
	else
		exec->ret = rv;
	return (rv);
}

int			ft_redir_execute(t_exec *exec)
{
	int pid;
	int rv;

	rv = 0;
	printf("fd--from %i -- fd--new %i\n", exec->fd_new[0], exec->fd_new[1]);
	//exec->full_name = ft_strjoin(exec->path, exec->name);
	if (!(pid = fork()))
		pipe_env(exec, exec->fd_new, 1, rv);
	g_data->pid = pid;
	if (exec->fd_new[0] != 0)
		close(exec->fd_new[0]);
	if (exec->fd_new[1] != 1)
		close(exec->fd_new[1]);
	wait(0);
	g_data->pid = 0;
	if (exec->full_name)
		exec->ret = WEXITSTATUS(rv);
	else
		exec->ret = rv;
	return (rv);
}

int ft_pipe(t_exec *pipe_list)
{
	int p_fd_new[2];

	while (pipe_list->pipe_to)
	{
		pipe(p_fd_new);
		pipe_list->fd_new[0] = p_fd_new[0];
		pipe_list->fd_new[1] = p_fd_new[1];
		pipe_list->ret = ft_pipe_part(pipe_list, p_fd_new, 1);
		pipe_list->pipe_to->ret = ft_pipe_part(pipe_list->pipe_to, p_fd_new, 0);
		pipe_list = pipe_list->pipe_to;
	}
	return (0);
}
