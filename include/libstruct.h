#ifndef LIBSTRUCT_H
# define LIBSTRUCT_H

# include "libincludes.h"

//like env but more convenient
typedef struct	s_env
{
	char		*key;
	char		*value;
	char		*link;
}				t_env;

//unusual env
typedef	struct	s_u_env
{
	//link to PWD in env_arr
	t_env		*l_pwd;
	//link to OLDPWD in env_arr
	t_env		*l_old_pwd;
	//link to PATH in env_arr
	t_env		*l_path;
	//PATH content
	char		**path_content;
}				t_u_env;

typedef	struct	s_data
{
	//Array of env_structures
	t_env		**env_arr;
	//unusual env
	t_u_env		*u_env;
	//link to original env
	char		**l_env;
}				t_data;

typedef struct	s_exec
{
	//ONLY NAME
	char		*name;
	//ONLY PATH
	char		*path;
	//[0] - exe name | [n] - NULL
	char		**argv;
	//l_env
	char		**env;
	//null if no
	t_exec		*pipe_to;
	t_exec		*pipe_from;
	//[0] - read [1] - write or *FILL WITH STD*
	int			fd_old[2];
	//fd ofter pipe or redir; -2 if no
	int			fd_new[2];
	int			ret;
}				t_exec
#endif
