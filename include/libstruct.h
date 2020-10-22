#ifndef LIBSTRUCT_H
# define LIBSTRUCT_H

# include "libincludes.h"

typedef struct	s_env
{
	char *key;
	char *value;
	char **link;
}				t_env;

typedef	struct	s_u_env
{
	t_env	l_pwd;
	t_env	l_old_pwd;
	t_env	l_path;
	char	**path_content;
}				t_u_env;

#endif
