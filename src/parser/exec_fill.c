/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_fill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:40 by ttamesha          #+#    #+#             */
/*   Updated: 2020/12/18 05:16:08 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parser.h"

t_exec	*exec_init(void)
{
	t_exec *exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->name = NULL;
	exec->path = NULL;
	exec->full_name = NULL;
	exec->argv = NULL;
	exec->env = g_data->l_env;
	exec->pipe_to = NULL;
	exec->pipe_from = NULL;
	exec->fd_new[0] = 0;
	exec->fd_new[1] = 1;
	exec->ret = 0;//-1
	return (exec);
}

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
		if ((cmd = ((t_token *)(*lptr)->content)->len) == C_END || cmd == C_PIPE)
			return ;
		*lptr = (*lptr)->next;
	}
}

t_dlist	*process_pipe(t_dlist *newlst, t_exec *exec)
{
	t_exec *newexec;

	free_tokens(&(g_data->lst));
	g_data->lst = newlst;
	//printf("NEW=%s\n", ((t_token *)((*lst)->content))->str);
	newexec = exec_init();
	if (!newexec)
		free_and_exit(ERRNO);
	exec->pipe_to = newexec;
	newexec->pipe_from = exec;
	return (exec_fill(newexec));
}

t_dlist	*end_cmd(t_dlist *lptr, t_exec *exec, int cmd)
{
	t_dlist	*newlst;

	newlst = NULL;
	if (lptr)
	{
		newlst = lptr->next;
		lptr->next = NULL;
	}
	ft_preprocess(exec);
	if (cmd == C_PIPE)
		return (process_pipe(newlst, exec));
	else
		return (newlst);
}

static t_dlist	*exec_arr_fill(t_dlist *lptr, t_exec *exec, char **argv)
{
	int		cmd;
	int		i;

	//if (argv[0])
		//printf("argv[0]=%s\n", argv[0]);//
	//printf("argv[0]=%s,%i\n", exec->argv[0], 0);
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
		{
			if (!(argv[++i] = ft_strdup(((t_token *)lptr->content)->str)))
				free_and_exit(ERRNO);
			//printf("%s, %i\n", argv[i], i);//
		}
		lptr = lptr->next;
	}
	return (end_cmd(lptr, exec, cmd));
	//return (NULL);
}

t_dlist	*exec_fill(t_exec *exec)
{
	t_dlist *lptr;
	int		len;

//printf("NEW=%s\n", ((t_token *)((*lst)->content))->str);
	len = cmd_len(g_data->lst);
	//printf("len=%i\n", len);
	if (!(exec->argv = (char **)ft_calloc(sizeof(char *), len + 1)))
	//if (!(exec->argv = (char **)malloc(sizeof(char) * (len + 1))))
		free_and_exit(ERRNO);
	lptr = g_data->lst;
	find_name(&lptr, exec, &(exec->argv[0]));
	//printf("argv[0]=%s\n", exec->argv[0]);
	return (exec_arr_fill(lptr, exec, exec->argv));
}
