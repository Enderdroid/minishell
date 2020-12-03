#ifndef LIBBUILTINS_H
# define LIBBUILTINS_H

# include "libincludes.h"

#define PATH_MAX 1024

int get_env_count();
int add_env(char *key, char *value);
int del_env(t_env *env);
int change_env_value(t_env *env, const char *value);
t_env *find_env_unset(char *key);

	int b_cd(char **n_path);
ssize_t b_echo(char **str);
ssize_t b_env(int fd);
ssize_t b_export(char **argv);
int b_pwd(int fd);
ssize_t b_unset(char **key);

#endif
