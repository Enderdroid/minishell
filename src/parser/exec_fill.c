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
	exec->fd_new[0] = -2;
	exec->fd_new[1] = -2;
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
		else if (cmd > 0)
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

t_dlist	*end_cmd(t_dlist **lst, t_dlist *lptr, t_exec *exec, int cmd)
{
	t_dlist	*newlst;

	newlst = lptr->next;
	lptr->next = NULL;
	if (cmd == C_END)
		return (newlst);
	return (process_pipe(lst, newlst, exec));
}

t_dlist	*exec_arr_fill(t_dlist **lst, t_dlist *lptr, t_exec *exec, char **argv)
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
				return (end_cmd(lst, lptr, exec, cmd));
			else if (!process_rdr(lst, exec, &lptr, argv))
				return (NULL);
			continue ;
		}
		else if ((cmd = ((t_token *)lptr->content)->len) > 0)
		{
			if (!(argv[++i] = ft_strdup(((t_token *)lptr->content)->str)))
				parser_exit(lst, NULL);
			printf("%s, %i\n", argv[i], i);//
		}
		lptr = lptr->next;
	}
	//argv[++i] = NULL;
	//printf("argv[++i]=%s,%i\n", exec->argv[i+1], i);
	return (NULL);
}

t_dlist	*exec_fill(t_dlist **lst, t_exec *exec)
{
	t_dlist *lptr;
	char	**argv;
	int		len;

//printf("NEW=%s\n", ((t_token *)((*lst)->content))->str);
	len = cmd_len(*lst, exec);
	//printf("len=%i\n", len);
	if (!(exec->argv = (char **)ft_calloc(sizeof(char *), len + 1)))
	//if (!(exec->argv = (char **)malloc(sizeof(char) * (len + 1))))
		parser_exit(lst, NULL);
	lptr = *lst;
	find_name(lst, &lptr, exec, &(exec->argv[0]));
	//printf("argv[0]=%s\n", exec->argv[0]);
	return (exec_arr_fill(lst, lptr, exec, exec->argv));
}
