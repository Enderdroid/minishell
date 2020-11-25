/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_redirect.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 19:52:49 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:49:29 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"
#include "../../include/error.h"
#include <fcntl.h>

static int	process_rdr_left(t_exec *exec, char *filename)
{
	if (exec->fd_new[0] > 1)
		close(exec->fd_new[0]);
	exec->fd_new[0] = open(filename, O_RDONLY);
	if (exec->fd_new[0] < 0)
		return (error_msg_auto(filename, 1));
	return (1);
}

static int	process_rdr_right(t_exec *exec, char *filename, int cmd)
{
	if (exec->fd_new[1] > 1)
		close(exec->fd_new[1]);
	if (cmd == C_RDR_R_DBL)
		exec->fd_new[1] = open(filename, O_CREAT | O_WRONLY | \
										O_APPEND, S_IRWXU | S_IROTH);
	if (cmd == C_RDR_R)
		exec->fd_new[1] = open(filename, O_CREAT | O_WRONLY | \
										O_APPEND, S_IRWXU | S_IROTH);
	if (exec->fd_new[1] < 0)
		return (error_msg_auto(filename, 1));
	return (1);
}

static int	error_msg_amb(char *filename)
{
	g_code = 1;
	error_msg_prompt(filename);
	write(2, "ambiguous redirect\n", 19);
	free_exec(g_data->exec);
	g_data->exec = NULL;
	return (0);
}

int			process_rdr(t_exec *exec, t_dlist **lptr, char **arr)
{
	char	*filename;
	int		cmd;

	cmd = ((t_token *)((*lptr)->content))->len;
	*lptr = (*lptr)->next;
	filename = ((t_token *)((*lptr)->content))->str;
	printf("rdr=%s\n", filename);//
	if (!((t_token *)((*lptr)->content))->len)
	{
		error_msg_amb(filename);
		return (0);
	}
	if (cmd == C_RDR_L)
	{
		if (!process_rdr_left(exec, filename))
			return (0);
	}
	else if (!process_rdr_right(exec, filename, cmd))
		return (0);
	*lptr = (*lptr)->next;
	if (!exec->name)
		find_name(lptr, exec, &arr[0]);
	return (1);
}
