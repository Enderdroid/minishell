#include "../../include/libincludes.h"
#include "../../include/libbuiltins.h"
#include "../../include/error.h"
#include <stdio.h>

void ft_pipe(t_exec *from, t_exec *to)
{
	int ind;
	char buf[256];
	char *j_buf;

	ft_execute(from);
	close(from->fd_new[1]);
	while (to->argv[ind])
		++ind;
	while (read(from->fd_new[0], buf, 256))
	{
		j_buf = to->argv[ind];
		to->argv[ind] = ft_strjoin(j_buf, buf);
		free(j_buf);
	}
	ft_execute(to);
}

int ft_preprocess(t_exec *exec)
{
	int ret;

	if (!(ft_strcmp(exec->name, "cd")))
		return (b_cd(exec->argv));
	if (!(ft_strcmp(exec->name, "echo")))
		return(b_echo(exec->argv, 1));
	if (!(ft_strcmp(exec->name, "env")))
		return(b_env(1));
	// if (!(ft_strcmp(exec->name, "exit")))
		// ret = b_exit();
	if (!(ft_strcmp(exec->name, "export")))
		return(b_export(exec->argv, 1));
	if (!(ft_strcmp(exec->name, "pwd")))
		return(b_pwd(1));
	if (!(ft_strcmp(exec->name, "unset")))
		return(b_unset(exec->argv));
	exec->path = s_in_path(g_data->u_env->path_content, exec->name);
	if (!(exec->path))
		//printf("%s: command not found", exec->name);
		error_msg_custom(exec->name, "command not found", 127);
	return (0);
}

//Дописать обработку пайпа билтинов и пайпа PATH

int ft_processor(t_exec *exec)
{
	t_exec *exec_buf;

	printf("\n[Processor started]\n");
	if (!exec->path)
		ft_preprocess(exec);
	if (!(exec->pipe_to))
		ft_execute(exec);
	exec_buf = exec;
	while (exec_buf->pipe_to)
	{
		ft_pipe(exec_buf, exec_buf->pipe_to);
		exec_buf = exec_buf->pipe_to;
	}
	printf("\n[Processor ended]\n");
	return (0);
}