//#include "../../include/libincludes.h"
#include "../../include/libstruct.h"
#include "../../include/error.h"

int	ft_preprocess(t_exec *exec) // поменять на void?
{
	int fs;

	if (!exec->name)
		return (0);
	if (!exec->path)
	{
		if (is_builtin(exec))
			return (1);
		exec->path = s_in_path(g_data->u_env->path_content, exec->name);
		if (!(exec->path))
		{
			error_msg_custom(exec->name, "command not found", 127);
			free_and_null(&exec->name);
		}
	}
	else if (!(fs = folder_search(exec->path, exec->name)))
	{
		error_msg_custom(exec->name_and_path, "No such file or directory", 127);
		free_and_null(&exec->name);
	}
	else if (fs == 2)
	{
		error_msg_custom(exec->name_and_path, "is a directory", 126);
		free_and_null(&exec->name);
	}
	return (0);
}
