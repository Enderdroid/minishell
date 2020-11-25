/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libstruct.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:51 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/26 01:26:26 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBSTRUCT_H
# define LIBSTRUCT_H

# include <stdio.h> //
# include "../libft/libft.h"
# include <unistd.h>
# include <stdlib.h>
# include "exit.h"

typedef struct			s_exec
{
	char				*name;
	char				*path;
	//[0] - exe name | [n] - NULL
	char				**argv;
	char				**env;
	//null if no
	struct s_exec		*pipe_to;
	struct s_exec		*pipe_from;
	//[0] - read [1] - write or *FILL WITH STD*
	//fd ofter pipe or redir; -2 if no
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
void					handle_signals(void);

#endif
