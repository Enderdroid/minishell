#ifndef LIBSTRUCT_H
# define LIBSTRUCT_H

#include <stdio.h> //

typedef struct			s_env
{
	char				*key;
	char				*value;
	char				**link;
}						t_env;

typedef	struct			s_u_env
{
	t_env				*l_pwd;
	t_env				*l_old_pwd;
	t_env				*l_path;
	char				**path_content;
}						t_u_env;

typedef	struct			s_data
{
	//Array of env_structures
	//how to make it **arr???
	t_env				*env_arr;
	//unusual env
	t_u_env				*u_env;
	//link to original env
	char				**l_env;
}						t_data;

typedef struct			s_exec
{
	//ONLY NAME
	char				*name;
	//ONLY PATH
	char				*path;
	//[0] - exe name | [n] - NULL
	char				**argv;
	//l_env
	char				**env;
	//null if no
	struct s_exec		*pipe_to;
	struct s_exec		*pipe_from;
	//[0] - read [1] - write or *FILL WITH STD*
	int					fd_old[2];
	//fd ofter pipe or redir; -2 if no
	int					fd_new[2];
	int					ret;
}						t_exec;

//global var
int g_code;
t_data *data;


#endif
