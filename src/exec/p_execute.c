#include "../../include/libincludes.h"
#include "../../include/error.h"

int builtin_call(t_exec *exec)
{
	if (!(ft_strcmp(exec->name, "cd")))
		return (b_cd(exec->argv));
	else if (!(ft_strcmp(exec->name, "echo")))
		return (b_echo(exec->argv, exec->fd_new[1]));
	else if (!(ft_strcmp(exec->name, "env")))
		return (b_env(1));
	// if (!(ft_strcmp(exec->name, "exit")))
	// ret = b_exit();
	//return(free_and_exit(0)); если нужна функция для выхода из проги
	else if (!(ft_strcmp(exec->name, "export")))
		return (b_export(exec->argv, exec->fd_new[1]));
	else if (!(ft_strcmp(exec->name, "pwd")))
		return (b_pwd(1));
	else if (!(ft_strcmp(exec->name, "unset")))
		return (b_unset(exec->argv));
	else
		return (-1);
}

int ft_execute(t_exec *exec, int fd, int rv)
{
	char *f_name;

	if (exec->fd_new[0] != 0 && exec->fd_new[1] != 1)
	{
		dup2(exec->fd_new[fd], fd);
		close(exec->fd_new[0]);
		close(exec->fd_new[1]);
	}
	if (exec->path)
	{
		f_name = ft_strjoin(exec->path, exec->name);
		//exec->name_and_path ? это строка без разбиения на path и name
		if (!f_name)
			free_and_exit(ERRNO); //для выхода по ошибке
		exit (rv);
	}
	else
		exec->ret = builtin_call(exec);
	return (exec->ret);
}

int ft_no_pipe(t_exec *exec)
{
	int f_ret;
	int rv;
	char *f_name;

	if (!(f_ret = fork()))
		ft_execute(exec, -1, rv);
	else
	{
		g_data->pid = f_ret;
		wait(0);
		g_data->pid = 0;
		if (!is_builtin(exec))
			exec->ret = WEXITSTATUS(rv);
	}
	return (rv);
}

int ft_pipe(t_exec *from, t_exec *to)
{
	int f_ret[2];
	int rv[2];
	char *f_name;

	if (!(f_ret[0] = fork()))
		ft_execute(from, 1, rv[1]);
	else
	{
		if (!(f_ret[1] == fork()))
			ft_execute(to, 0, rv[0]);
		else
		{
			close(from->fd_new[0]);
			close(from->fd_new[1]);
			wait(0);
			if (!is_builtin(from))
				from->ret = WEXITSTATUS(rv[1]);
			if (!is_builtin(to))
				to->ret = WEXITSTATUS(rv[0]);
		}
	}
	printf("\nEXEC ENDED\n");
	return (0);
}
