#include "../../include/parser.h"

int		cmd_type(char *cmd)
{
	if (*cmd == '|')
		return (C_PIPE);
	if (*cmd == '>')
	{
		if (*(cmd + 1) == '>')
			return (C_RDR_R_DBL);
		return (C_RDR_R);
	}
	if (*cmd == '<')
		return (C_RDR_L);
	if (*cmd == ';')
		return (C_END);
	return (-1);
}

void	free_tokens(t_dlist **lst)
{
	t_dlist *tmp;
	t_dlist *lptr;

	if (!lst || !*lst)
		return ;
	lptr = *lst;
	while (lptr)
	{
		tmp = lptr->next;
		if(((t_token *)(lptr->content))->str)
			free(((t_token *)(lptr->content))->str);
		free((t_token *)(lptr->content));
		free(lptr);
		lptr = tmp;
	}
	*lst = NULL;
}

int		quote_pair(char *input, int i)
{
	char quote;

	quote = input[i];
	while (input[++i])
	{
		if (input[i] == quote)
			break;
		else if (input[i] == '\\' && quote == '\"' && input[i + 1])
			++i;
	}
	return (i);
}

int	stradd(char **str, char *new)
{
	char *tmp;

	if (!new || !*str)
	{
		if (*str)
			free(*str);
		if (new)
			free(new);
		return (0);
	}
	tmp = *str;
	*str = ft_strjoin(tmp, new);
	free(tmp);
	free(new);
	if (!*str)
		return (0);
	return (1);
}

void	print_list(t_dlist *lst)
{
	while(lst)
	{
		printf("%s,", ((t_token *)(lst->content))->str);
		printf("%i->",((t_token *)(lst->content))->len);
		lst = (lst)->next;
	}
	printf("NULL\n");
}