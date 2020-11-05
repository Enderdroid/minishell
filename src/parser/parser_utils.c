#include "../../include/parser.h"

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
		//++i;
	}
	//if (input[i] == '\0')
	//	--i;
	//	write(2, "minishell: unclosed quote\n", 26); //???
	return (i);
}
