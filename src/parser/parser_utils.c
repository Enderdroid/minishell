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
		printf("str to free: %s\n", ((t_token *)(lptr->content))->str);
		if (((t_token *)(lptr->content))->str)
			free(((t_token *)(lptr->content))->str);
		free((t_token *)(lptr->content));
		free(lptr);
		lptr = tmp;
	}
	*lst = NULL;
}

int		stradd(char **str, char *new)
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

void	print_list(t_dlist *lst)//for tests
{
	while (lst)
	{
		printf("%s,", ((t_token *)(lst->content))->str);
		printf("%i->", ((t_token *)(lst->content))->len);
		lst = (lst)->next;
	}
	printf("NULL\n");
}
