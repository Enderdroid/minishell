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

int ft_execute(t_exec *exec, int fd, int rv);
int builtin_call(t_exec *exec);
int ft_no_pipe(t_exec *exec);
int ft_pipe(t_exec *from, t_exec *to);
int ft_preprocess(t_exec *exec);
void ft_pipe_proc(t_exec *from, t_exec *to);
int re_execute(t_exec *from, t_exec *to);
int is_builtin(t_exec *exec);
int realloc_env(int new_size, int old_size);
char *ft_realloc(char *str, int new_size);
int ft_processor(t_exec *exec);
char *s_in_path(char **path_val, char *name);

#endif
