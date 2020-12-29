#include "../../include/libincludes.h"

int p_sub_exec(t_exec *exec, int p_fd[2], int *rv)
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
		if (exec->full_name)
			execve(exec->full_name, exec->argv, g_data->l_env);
		else
			*rv = builtin_call(exec);
		exit(*rv);
	}
	else
		return (-1);
	g_data->pid = pid;
	return (0);
}

int ft_pipe_part(t_exec *exec, int p_fd[2], int fd)
{
	int ret;
	int rv;

	if (exec->fd_new[0] != 0 || exec->fd_new[1] != 1)
		p_fd = exec->fd_new;
	ret = p_sub_exec(exec, p_fd, &rv);

	// printf("CUR: %i - %i\n", p_fd[0], p_fd[1]);
	if (p_fd[0] != 0)
	{
		// printf("colsed: %i\n", p_fd[0]);
		close(p_fd[0]);
	}
	if (p_fd[1] != 1)
	{
		// printf("colsed: %i\n", p_fd[1]);
		close(p_fd[1]);
	}
	waitpid(g_data->pid, &rv, 0);
	g_data->pid = 0;
	g_data->code = WEXITSTATUS(rv);
	// printf("\n[GCODE == %i]\n", g_data->code);
	return (ret);
}

int ft_pipe(t_exec *pipe_list)
{
	int f_pipe[2][2];
	int fd_buf[2];
	int fd;
	
	fd = 1;
	fd_buf[0] = 0;
	while (pipe_list)
	{
		if (pipe_list->pipe_to != NULL)
		{
			pipe(f_pipe[fd]);
			// printf("OPENED : %i, %i\n", f_pipe[fd][0], f_pipe[fd][1]);
		}
		if (fd == 1)
		{
			fd_buf[1] = f_pipe[1][1];
			if (pipe_list->pipe_to == NULL)
				fd_buf[1] = 1;
		}
		else
		{
			fd_buf[0] = f_pipe[1][0];
			fd_buf[1] = f_pipe[0][1];
			if (pipe_list->pipe_to == NULL)
				fd_buf[1] = 1;
		}
		if (pipe_list->name)
			pipe_list->ret = ft_pipe_part(pipe_list, fd_buf, fd);
		else
		{
			if (fd_buf[0] != 0)
			{
				// printf("colsed: %i\n", fd_buf[0]);
				close(fd_buf[0]);
			}
			if (fd_buf[1] != 1)
			{
				// printf("colsed: %i\n", fd_buf[1]);
				close(fd_buf[1]);
			}
		}
		if (fd == 1)
			fd = 0;
		else
			fd = 1;
		pipe_list = pipe_list->pipe_to;		
		fd_buf[0] = f_pipe[0][0];
	}
	return (0);
}