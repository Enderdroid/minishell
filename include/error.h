/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 23:45:50 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/26 00:13:07 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERROR_H
# define ERROR_H

int		error_msg_auto(char *filename, int code);
int		error_msg_custom(char *filename, char *message, int code);
void	error_msg_prompt(char *filename);

#endif