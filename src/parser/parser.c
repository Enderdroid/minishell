/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/10/23 23:35:31 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
//#include "../../include/libstruct.h"
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

static void	syntax_err_msg(char *token)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	write(2, "`", 1);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
}

static int		move_to_quote_end(char *input, int i, char quote)
{
	while (input[++i])
	{
		if (input[i] == quote && (input[i - 1] != '\\' && i > 0))
			break;
	}
	return (i);
}

char	*skip_whitespaces(char *str)
{
	while (*str)
	{
		if (ft_isspace(*str))
			++str;
	}
	return (str);
}

static int	check_token(char c, int i, char *str)
{
	char	token[3];
	int		first;

	while (--i && ft_isspace(*str))
		++str;
	first = i > 0;
	
	//str = skip_whitespaces(str);
	//syntax_err_msg(token);
	return (0);

	return (1);
}

int				input_is_valid(char *input)
{
	int		i;
	char	c;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && (input[i - 1] != '\\' && i > 0))
			i = move_to_quote_end(input, i, input[i]);
		else if (ft_strchr(";&|><", input[i]))
		{
			c = input[i];
			while (input[i] == ' ')
				++i;
			if (!check_token(c, i + 1, input))
				return(0);
		}
	}
	return(1);
}

/*int				parse_line()
{
	if ()

}*/

void			parse_input(void)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(0, &line)) != 0 || *line)
	{
		if (!parse_line(&line))
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

int				main(int ac, char **av, char** envp)
{
	char	*line;
	int		i;
	int		size;

	(void)ac;
	(void)av;
	t_env *env = parse_env(envp, &size);
	t_u_env path_env = parse_u_env(env, size);
	/*
	i = -1;
	while (++i < size)
	{
		printf("%s\n", (env[i]).key);
		printf("%s\n", (env[i]).value);
		printf("%s\n", *((env[i]).link));
	}
	printf("%s\n", (path_env.l_old_pwd->key));
	printf("%s\n", (path_env.l_old_pwd->value));
	printf("%s\n", (path_env.l_pwd->key));
	printf("%s\n", (path_env.l_pwd->value));
	printf("%s\n", *(path_env.path_content));
	*/
}
