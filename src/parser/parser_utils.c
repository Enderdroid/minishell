#include "../../include/parser.h"

int not_shielded(char *input, int i)
{
	return ((input[i - 1] != '\\' && i > 0));
}

void free_tokens(t_dlist **lst)
{
	t_list *tmp;
	t_list *lptr;

	if (!lst || !*lst)
		return ;
	lptr = *lst;
	while (lptr)
	{
		tmp = lptr->next;
		free(((t_token *)(lptr->content))->str);
		free(lptr);
		lptr = tmp;
	}
	*lst = NULL;
}
