#include "../../include/libincludes.h"
#include "../../include/libbuiltins.h"
#include "../../include/error.h"
#include <stdio.h>//

int	is_builtin(t_exec *exec)
{
	if (!(ft_strcmp(exec->name, "cd")))
		return (1);
	else if (!(ft_strcmp(exec->name, "echo")))
		return (1);
	else if (!(ft_strcmp(exec->name, "env")))
		return (1);
	else if (!(ft_strcmp(exec->name, "exit")))
		return (1);
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
	printf("\n[Processor started]\n");

	if (exec->pipe_to)
		ft_pipe(exec);
	else if (exec->fd_new[0] == 0 && exec->fd_new[1] == 1)
	{
		// printf("EXEC\n");
		if (exec->name)
			ft_execute(exec);
	}
	else if (exec->name)
		ft_redir_execute(exec);

	printf("\n[Processor ended]\n");
	return (0);
}
