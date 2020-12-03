#ifndef LIBINCLUDES_H
# define LIBINCLUDES_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

# include "libstruct.h"
# include "../libft/libft.h"
# include "libbuiltins.h"
# include "libstruct.h"

int ft_execute(t_exec *exec);
int builtin_call(t_exec *exec);
int ft_pipe(t_exec *pipe_list);
int ft_redir_execute(t_exec *exec);
int ft_no_pipe(t_exec *exec);
void ft_pipe_proc(t_exec *from, t_exec *to);
int re_execute(t_exec *from, t_exec *to);

int realloc_env(int new_size, int old_size);
char *ft_realloc(char *str, int new_size);
int ft_processor(t_exec *exec);

#endif
