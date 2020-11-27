#include "../../include/libincludes.h"
#include "../../include/libbuiltins.h"
#include "../../include/error.h"
#include <stdio.h>

void ft_pipe_proc(t_exec *from, t_exec *to)
{
	char buf[256];
	char *j_buf;

	int fd_new[2];
	pipe(fd_new);
	from->fd_new[0] = fd_new[0];
	from->fd_new[1] = fd_new[1];
	to->fd_new[0] = fd_new[0];
	to->fd_new[1] = fd_new[1];
	ft_pipe(from, to);
}

int is_builtin(t_exec *exec)
{
	if (!(ft_strcmp(exec->name, "cd")))
		return (1);
	else if (!(ft_strcmp(exec->name, "echo")))
		return (1);
	else if (!(ft_strcmp(exec->name, "env")))
		return (1);
	// if (!(ft_strcmp(exec->name, "exit")))
	// ret = b_exit();
	else if (!(ft_strcmp(exec->name, "export")))
		return (1);
	else if (!(ft_strcmp(exec->name, "pwd")))
		return (1);
	else if (!(ft_strcmp(exec->name, "unset")))
		return (1);
	else
		return (0);
}

//Дописать обработку пайпа билтинов и пайпа PATH

int ft_processor(t_exec *exec)
{
	t_exec *exec_buf;
	int fd_new[2];

	printf("\n[Processor started]\n");
	//ft_preprocess(exec);
	exec_buf = exec;
	if (exec->pipe_to)
		while (exec->pipe_to)
		{
			if (exec->name) //если exec->name == NULL, пропускаем команду? добавила, чтоб не сегалось
			//exec->name == NULL если файла/команды нет, если именем был несуществующий $env или если была ошибка редиркта
				ft_pipe_proc(exec, exec->pipe_to);
			exec = exec->pipe_to;
		}
	else if (exec->name) // добавила условие для exec->name (exec всегда true)
		ft_no_pipe(exec);
	printf("\n[Processor ended]\n");
	return (0);
}
