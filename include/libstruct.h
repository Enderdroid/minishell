#ifndef LIBSTRUCT_H
# define LIBSTRUCT_H

#include <stdio.h> //

typedef struct	s_env
{
	char *key;
	char *value;
	char **link;
}				t_env;

typedef	struct	s_u_env
{
	t_env	*l_pwd;
	t_env	*l_old_pwd;
	t_env	*l_path;
	char	**path_content;
}				t_u_env;

typedef struct	s_exec
{
	char		*name;
	char		*path;
	char		**argv;
	char		**env;
	struct s_exec		*pipe;
	int			fd;
	int			ret;
}				t_exec;
//global var
int g_code;
t_env *env;

#endif
