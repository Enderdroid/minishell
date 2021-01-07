/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:40 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/07 16:07:57 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

static int		cmd_len(t_dlist *lptr)
{
	int len;
	int cmd;

	len = 0;
	while (lptr)
	{
		if ((cmd = ((t_token *)lptr->content)->len) < 0)
		{
			if (cmd == C_END || cmd == C_PIPE)
				return (len);
		}
		else if (cmd > 0)
			++len;
		lptr = lptr->next;
	}
	return (len);
}

static void		go_to_cmd_end(t_dlist **lptr)
{
	int cmd;

	while (*lptr)
	{
		if ((cmd = ((t_token *)(*lptr)->content)->len) == C_END \
												|| cmd == C_PIPE)
			return ;
		*lptr = (*lptr)->next;
	}
}

static t_dlist	*end_cmd(t_dlist *lptr, t_exec *exec, int cmd)
{
	t_dlist	*newlst;
	t_exec	*newexec;

	newlst = NULL;
	if (lptr)
	{
		newlst = lptr->next;
		lptr->next = NULL;
	}
	ft_preprocess(exec);
	if (cmd == C_PIPE)
	{
		free_tokens(&(g_data->lst));
		g_data->lst = newlst;
		newexec = exec_init();
		if (!newexec)
			free_and_exit(ERRNO);
		exec->pipe_to = newexec;
		newexec->pipe_from = exec;
		return (exec_fill(newexec));
	}
	else
		return (newlst);
}

static t_dlist	*exec_arr_fill(t_dlist *lptr, t_exec *exec, char **argv)
{
	int		cmd;
	int		i;

	cmd = C_END;
	i = 0;
	while (lptr)
	{
		if ((cmd = ((t_token *)lptr->content)->len) < 0)
		{
			if (cmd == C_END || cmd == C_PIPE)
				return (end_cmd(lptr, exec, cmd));
			else if (!(process_rdr(exec, &lptr, argv)))
			{
				free_and_null(&(exec->name));
				go_to_cmd_end(&lptr);
			}
			continue ;
		}
		else if ((cmd = ((t_token *)lptr->content)->len) > 0)
			if (!(argv[++i] = ft_strdup(((t_token *)lptr->content)->str)))
				free_and_exit(ERRNO);
		lptr = lptr->next;
	}
	return (end_cmd(lptr, exec, cmd));
}

t_dlist			*exec_fill(t_exec *exec)
{
	t_dlist *lptr;
	int		len;

	len = cmd_len(g_data->lst);
	if (!(exec->argv = (char **)ft_calloc(sizeof(char *), len + 1)))
		free_and_exit(ERRNO);
	lptr = g_data->lst;
	find_name(&lptr, exec, &(exec->argv[0]));
	return (exec_arr_fill(lptr, exec, exec->argv));
}
