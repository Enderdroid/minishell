#include "../../include/parser.h"

static void		fill_env_arr(t_env **env, char **envp)
{
	int		i;
	char	**tmp;

	i = 0;
	while(envp[i])
	{
		if (!(env[i] = (t_env *)malloc(sizeof(t_env))))
			free_and_exit(ERRNO);
		if (!(tmp = ft_split(envp[i], '=')))
			free_and_exit(ERRNO);
		env[i]->key = ft_strdup(tmp[0]);
		env[i]->value = ft_strdup(tmp[1]);
		if (!env[i]->key || !env[i]->value)
		{
			free_arr(tmp);
			free_and_exit(ERRNO);
		}
		free_arr(tmp);
		env[i]->link = &(envp[i]);
		++i;
	}
	env[i] = NULL;
}

static t_env	**parse_env(char **envp, int size)
{
	t_env	**env;

	if (!(env = (t_env **)malloc(sizeof(t_env *) * size )))
	{
		free(data);
		exit_with_errno();
	}
	fill_env_arr(env, envp);
	return (env);
}

static t_u_env	*parse_u_env(t_env **env, int size)
{
	t_u_env	*path_env;
	int		i;

	path_env = (t_u_env *)malloc(sizeof(t_u_env));
	if (!path_env)
		free_and_exit(ERRNO);
	path_env->l_pwd = NULL;
	path_env->l_old_pwd = NULL;
	path_env->l_path = NULL;
	path_env->path_content = NULL;
	i = -1;
	while (++i < size)
	{
		if (ft_strcmp(env[i]->key, "PWD") == 0)
			path_env->l_pwd = env[i];
		if (ft_strcmp(env[i]->key, "OLDPWD") == 0)
			path_env->l_old_pwd = env[i];
		if (ft_strcmp(env[i]->key, "PATH") == 0)
		{
			path_env->l_path = env[i];
			path_env->path_content = ft_split(env[i]->value, ':');
			if (!path_env->path_content)
				free_and_exit(ERRNO);
		}
	}
	return (path_env);
}

void			init_data(char **envp)
{
	int		size;
	t_env	**env;

	g_code = 0;
	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		exit_with_errno();
	size = 0;
	//printf("THIS == %i]\n", size);
	while (envp[size])
		++size;
	env = parse_env(envp, size);
	data->env_arr = env;
	data->u_env = parse_u_env(env, size);
	data->l_env = envp;
	data->exec = NULL;
}
