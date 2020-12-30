/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:41:34 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/30 23:31:55 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static void		fill_env_arr(t_env **env, char **l_env, char **envp)
{
	int		i;
	char	**tmp;

	i = -1;
	while (envp[++i])
	{
		if (!(l_env[i] = ft_strdup(envp[i])))
			free_and_exit(ERRNO);
		if (!(env[i] = (t_env *)malloc(sizeof(t_env))))
			free_and_exit(ERRNO);
		if (!(tmp = ft_split(envp[i], '=')))
			free_and_exit(ERRNO);
		env[i]->key = ft_strdup(tmp[0]);
		env[i]->value = (tmp[1]) ? ft_strdup(tmp[1]) : ft_strdup("");
		free_arr(tmp);
		if (!env[i]->key || !env[i]->value)
			free_and_exit(ERRNO);
	}
}

static t_env	**parse_env(char **envp, int size)
{
	t_env	**env;

	if (!(env = (t_env **)ft_calloc(sizeof(t_env *), (size + 1))))
	{
		free(g_data);
		exit_with_errno();
	}
	if (!(g_data->l_env = (char **)ft_calloc(sizeof(char *), (size + 1))))
	{
		free(g_data);
		free(env);
		exit_with_errno();
	}
	fill_env_arr(env, g_data->l_env, envp);
	/*for(int i = 0; i < size+1; ++i)
	{
		printf("%s\n", g_data->env_arr[i]);
		printf("key=%s, value=%s\n", env[i]->key,env[i]->value);//
	}*/
	return (env);
}

static t_u_env	*parse_u_env(t_env **env, int size)
{
	t_u_env	*path_env;
	int		i;

	if (!(path_env = (t_u_env *)malloc(sizeof(t_u_env))))
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

	if (!(g_data = (t_data *)malloc(sizeof(t_data))))
		exit_with_errno();
	size = 0;
	while (envp[size])
		++size; //printf("%s\n", envp[size]);
	env = parse_env(envp, size);
	g_data->env_arr = env;
	g_data->u_env = parse_u_env(env, size);
	g_data->exec = NULL;
	g_data->lst = NULL;
	g_data->code = 0;
	g_data->pid = 0;
}
