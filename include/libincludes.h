#ifndef LIBINCLUDES_H
# define LIBINCLUDES_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>

# include "libstruct.h"
# include "../libft/libft.h"
# include "libstruct.h"

int ft_execute(t_exec *exec);
int realloc_env(int new_size, int old_size);
char *ft_realloc(char *str, int new_size);
int ft_processor(t_exec *exec);
char *s_in_path(char **path_val, char *name);

#endif
