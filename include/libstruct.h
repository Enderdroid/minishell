/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstruct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:51 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:32:56 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSTRUCT_H
# define LIBSTRUCT_H

# include "../libft/libft.h"
# include "exit.h"
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>

# define COLOR "\e[0;36m"
# define RESET "\e[0m"

typedef struct			s_exec
{
	char				*name;
	char				*path;
	char				*full_name;
	char				**argv;
	char				**env;
	struct s_exec		*pipe_to;
	struct s_exec		*pipe_from;
	int					fd_new[2];
	int					ret;
}						t_exec;

typedef struct			s_env
{
	char				*key;
	char				*value;
}						t_env;

typedef	struct			s_u_env
{
	t_env				*l_pwd;
	t_env				*l_old_pwd;
	t_env				*l_path;
	char				**path_content;
	char				*home;
}						t_u_env;

typedef	struct			s_data
{
	t_env				**env_arr;
	t_u_env				*u_env;
	char				**l_env;
	t_exec				*exec;
	t_dlist				*lst;
	int					code;
	int					pid;
}						t_data;

t_data *g_data;

void					init_data(char **envp);
void					free_data(void);
void					free_exec(t_exec *exec);
void					catch_signals(void);
t_env					*find_env_b(char *key);
char					*find_env(char *key);
int						is_builtin(t_exec *exec);
void					ft_preprocess(t_exec *exec);
char					*s_in_path(char *name, t_env *l_path);
int						folder_search(char *path, char *name);
#endif
