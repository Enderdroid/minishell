/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/10/25 20:11:12 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

t_env			*parse_env(char **envp, int *size)
{
	t_env	*env;
	char	**tmp;
	int		i;

	*size = 0;
	while (envp[*size])
		++(*size);
	env = (t_env*)malloc(sizeof(t_env) * *size);
	// if (!env)
		// ERROR
	i = -1;
	while(envp[++i])
	{
		tmp = ft_split(envp[i], '=');
		env[i].key = ft_strdup(tmp[0]);
		env[i].value = ft_strdup(tmp[1]);
		free_arr(tmp);
		env[i].link = &(envp[i]);
	}
	return (env);
}

t_u_env			parse_u_env(t_env *env, int size)
{
	t_u_env	path_env;
	int		i;

	path_env.l_pwd = NULL;
	path_env.l_old_pwd = NULL;
	path_env.l_path = NULL;
	path_env.path_content = NULL;
	i = -1;
	while (++i < size)
	{
		if (ft_strcmp(env[i].key, "PWD") == 0)
			path_env.l_pwd = &env[i];
		if (ft_strcmp(env[i].key, "OLDPWD") == 0)
			path_env.l_old_pwd = &env[i];
		if (ft_strcmp(env[i].key, "PATH") == 0)
		{
			path_env.l_path = &env[i];
			path_env.path_content = ft_split(env[i].value, ':');
		}
	}
	return(path_env);
}

int				parse_line(char *line)
{
	if (input_is_valid(line))
	{

		return (1);
	}
	return (0);
}

void			parse_input(void)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(STDIN_FILENO, &line)) != 0 || *line)
	{
		if (!parse_line(line))
		{
			//free_and_exit();
		}
	}
	if (ret == 0)
	{
		//free(line);
		//free_and_exit();
	}
	free(line);
}
