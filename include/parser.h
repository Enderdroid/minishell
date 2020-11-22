/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/17 16:01:44 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:28:06 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "parserstruct.h"

t_exec	*exec_init(void);
t_dlist	*exec_fill(t_exec *exec);
int		process_rdr(t_exec *exec, t_dlist **lptr, char **argv);
void	find_name(t_dlist **lptr, t_exec *exec, char **argv);

#endif
