/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tkleiner <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:01:44 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/30 20:36:01 by tkleiner         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "parserstruct.h"
# define COLOR "\e[0;36m"
# define RESET "\e[0m"

t_exec	*exec_init(void);
t_dlist	*exec_fill(t_exec *exec);
int		process_rdr(t_exec *exec, t_dlist **lptr, char **argv);
void	find_name(t_dlist **lptr, t_exec *exec, char **argv);

#endif
