/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:45:50 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:34:19 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

void	error_msg_auto(int *ret, char *filename, int code);
void	error_msg_custom(int *ret, char *filename, char *message, int code);
void	error_msg_prompt(char *filename);

#endif
