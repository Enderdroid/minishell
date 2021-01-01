//#include "../../include/libincludes.h"
#include "../../include/libstruct.h"
#include "../../include/error.h"

static void	check_filepath(t_exec *exec, char mode, int fs)
{
	if (fs == 0)
	{
		//printf("fs=%i\n", fs);
		if (mode == 'n')
			execve(exec->full_name, exec->argv, exec->env);
		else
			execve(exec->path, exec->argv, exec->env);
		error_msg_auto(&exec->ret, exec->full_name, (errno == 2) ? 127 : 126);
		free_and_null(&exec->name);
	}
	else if (fs == 2)
	{
		error_msg_custom(&exec->ret, exec->full_name, "is a directory", 126);
		free_and_null(&exec->name);
	}
}

static void	check_dir(t_exec *exec)
{
	int		fs;
	char	*new_path;
	char	*s;

	if ((s = ft_strrchr(exec->path, '/')))
	{
		exec->name = ft_strdup(s + 1);
		new_path = ft_substr(exec->path, 0, s - exec->path);
	}
	else
	{
		exec->name = ft_strdup(exec->path);
		new_path = find_env(ft_strdup("PWD"));
	}
	if (!new_path || !exec->name)
		free_and_exit(ERRNO);
	if ((fs = folder_search(new_path, exec->name)) == 1)
	{
		error_msg_custom(&exec->ret, exec->full_name, "Not a directory", 126);
		free_and_null(&exec->name);
	}
	else
		check_filepath(exec, 'd', fs);
	free(new_path);
}

static void	set_full_name(t_exec *exec)
{
	if (!(exec->path = s_in_path(exec->name)))
	{
		error_msg_custom(&exec->ret, exec->name, "command not found", 127);
		free_and_null(&exec->name);
	}
	else if (ft_strcmp(exec->path, "") == 0)
	{
		error_msg_custom(&exec->ret, exec->name, "No such file or directory", 127);
		free_and_null(&exec->name);
	}
	else if (!(exec->full_name = ft_strjoin(exec->path, exec->name)))
		free_and_exit(ERRNO);
}

void		ft_preprocess(t_exec *exec)
{
	if (!exec->name)
	{
		if (!exec->ret)
			g_data->code = 0;
	}
	else if (!exec->path)
	{
		if (is_builtin(exec))
			return ;
		set_full_name(exec);
	}
	else if (!ft_strcmp(exec->name, ""))
	{
		free_and_null(&exec->name);
		(ft_strcmp(exec->path, "")) ? check_dir(exec) : \
		error_msg_custom(&exec->ret, exec->full_name, "is a directory", 126);
	}
	else
		check_filepath(exec, 'n', folder_search(exec->path, exec->name));
}
