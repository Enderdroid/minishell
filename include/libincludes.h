/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libincludes.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:34:45 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:34:46 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBINCLUDES_H
# define LIBINCLUDES_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>

# include "libstruct.h"
# include "libbuiltins.h"

int		ft_execute(t_exec *exec);
int		builtin_call(t_exec *exec);
void	ft_pipe(t_exec *pipe_list);
int		redir_execute(t_exec *exec);
int		ft_no_pipe(t_exec *exec);
void	ft_pipe_proc(t_exec *from, t_exec *to);
int		re_execute(t_exec *from, t_exec *to);

int		sub_add_env(int old_size);
int		sub_del_env(int old_size, t_env *env);
char	*ft_realloc(char *str, int new_size);
int		ft_processor(t_exec *exec);
#endif
