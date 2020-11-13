#include "../../include/parser.h"

t_exec	*exec_init()
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
	//exec->fd_old
	//exec->fd_new
	exec->ret = 0;
	return (exec);
}

int		cmd_len(t_dlist *lptr)
{
	int		len;

	len = 0;
	while (lptr)
	{
		if(((t_token *)lptr->content)->len < 0)
			return (len);
		++len;
		lptr = lptr->next;
	}
	return (len);
}

void	fill_name_path(char *str, t_exec *exec, char **name, t_dlist **lst)
{
	char *s;

	if (*(str + 1) == '/')
	{
		if (*str == '~')
			if (!(exec->path = find_env(ft_strdup("HOME"))))
				//free_exec(exec);
				parser_exit(lst, NULL);
		if (*str == '.')
			if (!(exec->path = find_env(ft_strdup("PWD"))))
				//free_exec(exec);
				parser_exit(lst, NULL);
	}
	s = ft_strrchr(str, '/');
	exec->name = (s) ? ft_strdup((s + 1)) : ft_strdup(str);
	if (!exec->name)
		//free_exec(exec);
		parser_exit(lst, NULL);
	if (!(*name = ft_strdup(exec->name))) //argv[0]
		//free_exec(exec);
		parser_exit(lst, NULL);
	if (s)
	{
		exec->path = (exec->path) ? ft_strjoin(exec->path, ft_substr(str, 0, s - str)) \
								: ft_substr(str, 0, s - str);
		if (!exec->path)
		//free_exec(exec);
			parser_exit(lst, NULL);
	}
}

void	process_cmd(t_dlist **lst, t_dlist *newlst, t_exec *exec, int cmd) //redirecs???
{
	free_tokens(lst);
	*lst = newlst;
	t_exec *newexec = exec_init();
	if (cmd == C_PIPE)
	{
		exec->pipe_to = newexec;
		newexec->pipe_from = exec;
	}

	exec_fill(lst, newexec);
}

t_dlist	*exec_arr_fill(t_dlist **lst, t_dlist *lptr, t_exec *exec, char **argv)
{
	t_dlist *newlst;
	int		i;

	i = 0;
	while (lptr)
	{
		if (((t_token *)lptr->content)->len < 0)
		{
			newlst = lptr->next;
			lptr->next = NULL;
			if(((t_token *)lptr->content)->len == C_END)
				return (newlst);
			process_cmd(lst, newlst, exec, (((t_token *)lptr->content)->len));
		}
		if (!(argv[++i] = ft_strdup(((t_token *)lptr->content)->str)))
			//free_exec
			parser_exit(lst, NULL);
		lptr = lptr->next;
	}
	return (NULL);
}

t_dlist	*exec_fill(t_dlist **lst, t_exec *exec)
{
	t_dlist *lptr;
	char	**argv;
	int		len;

	len = cmd_len(*lst);
	if (!(argv = (char **)ft_calloc(sizeof(char), len + 1)))
		//free_exec(exec);
		parser_exit(lst, NULL);
	lptr = *lst;
	if (((t_token *)(*lst)->content)->len >= 0)
	{
		fill_name_path(((t_token *)(*lst)->content)->str, exec, &argv[0], lst);
		lptr = (*lst)->next;
	}
	return (exec_arr_fill(lst, lptr, exec, argv));
}

void	analise_tokens(t_dlist **lst)
{
	int		len;
	t_dlist	*newlst;
	t_exec	*exec;

	while (!*lst)
	{
		len = 0;
		if (!(exec = exec_init()))
			parser_exit(lst, NULL);
		newlst = exec_fill(lst, exec);
		free_tokens(lst);
		*lst = newlst;
		//send exec
	}
	parse_input(0, lst);
}

/*void	free_tokens_part(t_dlist **lst)
{
	t_dlist *tmp;
	t_dlist *lptr;

	if (!lst || !*lst)
		return ;
	lptr = *lst;
	//1st token
	//lptr = lptr->next;
	while (lptr)
	{
		//argv
		if(is_token_end((t_token *)(lptr->content)))
		{
			tmp = lptr->next;
			lptr->next = NULL;
			free_tokens(lst);
			*lst = tmp;
			(*lst)->prev = NULL;
		}
		lptr = lptr->next;
	}
}*/

/*t_dlist	*split_tokens(t_dlist **lst, int *len)
{
	t_dlist	*newlst;
	t_dlist	*lptr;

	lptr = *lst;
	while (lptr)
	{
		if(is_token_end((t_token *)(lptr->content)))
		{
			newlst = lptr->next;
			lptr->next = NULL;
			return (newlst);
		}
		++(*len);
		lptr = lptr->next;
	}
	return (NULL);
}*/

