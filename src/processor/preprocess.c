//#include "../../include/libincludes.h"
#include "../../include/libstruct.h"
#include "../../include/error.h"

static void	check_name(t_exec *exec)
{
	int fs;

	if (!(fs = folder_search(exec->path, exec->name)))
	{
		//printf("fs=%i\n", fs);
		execve(exec->full_name, exec->argv, exec->env);
		error_msg_auto(exec->full_name, (errno == 2) ? 127 : 126);
		free_and_null(&exec->name);
	}
	else if (fs == 2)
	{
		error_msg_custom(exec->full_name, "is a directory", 126);
		free_and_null(&exec->name);
	}
}

static void	search_dir(t_exec *exec, int fs)
{
	if (fs == 0)
	{
		//printf("fs=%i\n", fs);
		execve(exec->path, exec->argv, exec->env);
		error_msg_auto(exec->full_name, (errno == 2) ? 127 : 126);
	}
	else if (fs == 2)
		error_msg_custom(exec->full_name, "is a directory", 126);
	else
		error_msg_custom(exec->full_name, "Not a directory", 126);
	free_and_null(&exec->name);
}

static void	check_dir(t_exec *exec)
{
	int		fs;
	char	*new_name;
	char	*new_path;
	char	*s;

	if ((s = ft_strrchr(exec->path, '/')))
	{
		if (!(new_name = ft_strdup(s + 1)))
			free_and_exit(ERRNO);
		if (!(new_path = ft_substr(exec->path, 0, s - exec->path)))
			free_and_exit(ERRNO);
	}
	else
	{
		if (!(new_name = ft_strdup(exec->path)))
			free_and_exit(ERRNO);
		if (!(new_path = find_env(ft_strdup("PWD"))))
			free_and_exit(ERRNO);
	}
	search_dir(exec, folder_search(new_path, new_name));
	free(new_name);
	free(new_path);
}

int			ft_preprocess(t_exec *exec) // поменять на void?
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
	else if (!ft_strcmp(exec->name, ""))
		check_dir(exec);
	else
		check_name(exec);
	return (0);
}
