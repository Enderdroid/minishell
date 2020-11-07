#include "../../include/parser.h"

char	*tokenize_str(char *str, int len) //, t_dlist **lst
{
	char	*res;
	int		i;
	int		q;

	i = 0;
	q = 0;
	res = malloc(sizeof(char) * (len + 1));
	//if (!res) //ERROR
	while(i < len)
	{
		if (str[i] == '\"')
		{
			res[i] = '0';
			q = (q) ? 0 : 1;
		}
		else if (str[i] == '\'' && !q)
		{
			res[i] = '0';
			while (str[++i] && str[i] != '\'')
				res[i] = '1';
			if (str[i])
				res[i] = '0';
		}
		else if (str[i] == '\\' && (!q || ft_strchr("$\"\\\0", str[i + 1])))
		{
			res[i] = '0';
			if (str[++i])
				res[i] = '1';
		}
		else if (str[i] == '$' && !ft_strchr(" ~:/.,^+=\\\%\0", str[i + 1]) \
										&& !(str[i + 1] == '\"' && q))
			res[i] = '2';
		else
			res[i] = '1';
		++i;
	}
	res[len] = '\0';
	return (res);
}

void	tokenize_lst(t_dlist **lst)
{
	t_dlist	*ptr;
	char	*mask;

	ptr = *lst;
	while (ptr)
	{
		if (((t_token *)(ptr->content))->len > 0)
		{
			mask = tokenize_str((((t_token *)(ptr->content))->str), ((t_token *)(ptr->content))->len); //, lst
			printf("%s\n", mask);//
			correct_str(&(((t_token *)(ptr->content))->str), &(((t_token *)(ptr->content))->len), &mask); //, lst
			printf("%s\n", ((t_token *)(ptr->content))->str);//
		}
		ptr = ptr->next;
	}
	//if (unfinished)
	//parse_input(1, &ptr);
}