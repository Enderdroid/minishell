#ifndef LIBSTRUCT_H
# define LIBSTRUCT_H

# include "libincludes.h"

typedef struct	s_env
{
	char *key;
	char *value;
	char *link;
}				t_env;

typedef	struct	s_u_env
{
	t_env	*l_pwd;
	t_env	*l_old_pwd;
	t_env	*l_path;
	char	**path_content;
}				t_u_env;

typedef	struct	s_data
{
	t_env	**env_arr;
	t_u_env	*u_env;
	char	**l_env;
}				t_data;

typedef struct	s_exec
{
	char	*name;
	char	*path;
	char	**argv;
	char	**env;
	t_exec	*pipe_to;
	int		fd;
	int		ret;
}				t_exec
#endif
