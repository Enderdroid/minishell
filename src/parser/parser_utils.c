#include "../../include/parser.h"


/*int		stradd(char **str, char *new)
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
}*/

void	print_list(t_dlist *lst)//for tests
{
	while (lst)
	{
		printf("[%s,", ((t_token *)(lst->content))->str);
		printf("%i]->", ((t_token *)(lst->content))->len);
		lst = (lst)->next;
	}
	printf("NULL\n");
}
