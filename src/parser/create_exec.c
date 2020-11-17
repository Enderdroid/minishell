#include "../../include/parser.h"

t_exec	*exec_init(void)
{
	t_exec *exec;

	exec = (t_exec *)malloc(sizeof(t_exec));
	if (!exec)
		return (NULL);
	exec->name = NULL;
	exec->path = NULL;
	exec->argv = NULL;
	exec->env = data->l_env;
	exec->pipe_to = NULL;
	exec->pipe_from = NULL;
	//exec->fd_old = {-2, -2};
	exec->fd_new[0] = -2;//read
	exec->fd_new[1] = -2;//write
	exec->ret = 0;
	return (exec);
}

int		cmd_len(t_dlist *lptr, t_exec *exec)
{
	int len;
	int cmd;

	len = (exec->pipe_from) ? 1 : 0;
	while (lptr)
	{
		if((cmd = ((t_token *)lptr->content)->len) < 0)
		{
			if (cmd == C_END || cmd == C_PIPE)
				return (len);
		}
		else
			++len;
		lptr = lptr->next;
	}
	return (len);
}

t_dlist	*process_pipe(t_dlist **lst, t_dlist *newlst, t_exec *exec) //redirecs???
{
	t_exec *newexec;

	free_tokens(lst);
	*lst = newlst;
	//printf("NEW=%s\n", ((t_token *)((*lst)->content))->str);
	newexec = exec_init();
	exec->pipe_to = newexec;
	newexec->pipe_from = exec;
	return (exec_fill(lst, newexec));
}

t_dlist	*exec_arr_fill(t_dlist **lst, t_dlist *lptr, t_exec *exec, char **argv)
{
	t_dlist	*newlst;
	int		cmd;
	int		i;

	i = 0;
	while (lptr)
	{
		if ((cmd = ((t_token *)lptr->content)->len) < 0)
		{
			if (cmd == C_END || cmd == C_PIPE)
			{
				newlst = lptr->next;
				lptr->next = NULL;
				if (cmd == C_END)
					return (newlst);
				return (process_pipe(lst, newlst, exec));
			}
			else if (!process_rdr(lst, exec, &lptr, argv))
				return (NULL);
		}
		else if (!(argv[++i] = ft_strdup(((t_token *)lptr->content)->str)))
			parser_exit(lst, NULL);
		printf("%s, %i\n", argv[i], i);//
		lptr = lptr->next;
	}
	return (NULL);
}

t_dlist	*exec_fill(t_dlist **lst, t_exec *exec)
{
	t_dlist *lptr;
	char	**argv;
	int		len;

//printf("NEW=%s\n", ((t_token *)((*lst)->content))->str);
	len = cmd_len(*lst, exec);
	if (!(argv = (char **)ft_calloc(sizeof(char), len + 1)))
		parser_exit(lst, NULL);
	lptr = *lst;
	if (((t_token *)(*lst)->content)->len >= 0)
	{
		fill_name_path(((t_token *)(*lst)->content)->str, exec, &argv[0], lst);

		/*printf("head name = %s\n", data->exec->name);//
		if (data->exec->pipe_to)
			printf("next name = %s\n", ((t_exec *)(data->exec->pipe_to))->name);//
		printf("head path = %s\n", data->exec->path);*/

		lptr = (*lst)->next;
	}
	return (exec_arr_fill(lst, lptr, exec, argv));
}
