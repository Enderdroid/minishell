/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libbuiltins.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 16:34:28 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:34:39 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBBUILTINS_H
# define LIBBUILTINS_H

# include "libincludes.h"

# define PATH_MAX 1024

t_env	*add_env(char *key, char *value, char **to_free);
int		del_env(t_env *env);
t_env	*change_env_value(t_env *env, char *key, char *value, char **to_free);
void	b_put_error(char *name, char *arg, char *message, int code);
int		is_env(char *arg);
void	remake_lenv();
int		b_cd(t_exec *exec);
int		b_echo(t_exec *exec);
int		b_env(t_exec *exec);
int		b_export(t_exec *exec);
int		b_pwd(t_exec *exec);
int		b_unset(t_exec *exec);
int		b_exit(t_exec *exec);
#endif
