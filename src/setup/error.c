/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:28:35 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/02 23:28:36 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libstruct.h"
#include "../../include/error.h"

void	error_msg_auto(int *ret, char *filename, int code)
{
	g_data->code = code;
	error_msg_prompt(filename);
	ft_putendl_fd(strerror(errno), 2);
	*ret = code;
}

void	error_msg_custom(int *ret, char *filename, char *message, int code)
{
	g_data->code = code;
	error_msg_prompt(filename);
	ft_putendl_fd(message, 2);
	*ret = code;
}

void	error_msg_prompt(char *filename)
{
	write(2, "minishell: ", 11);
	write(2, filename, ft_strlen(filename));
	write(2, ": ", 2);
}

