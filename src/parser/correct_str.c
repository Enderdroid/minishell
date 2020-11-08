
#include "../../include/parser.h"

static char	*substr_filtered(char *str, char *mask, int len, int end)
{
	char	*res;
	int		start;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	//printf("%s\n, %s\n", str, mask);
	i = 0;
	start = 0;
	while (start < end)
	{//printf("%c, %c\n", mask[start], str[start]);
		if (mask[start] == '1')
		{
			res[i] = str[start];
			//printf("%c,%i,%c\n", res[i], start, str[start]);
			++i;
		}
		++start;
	}
	res[i] = '\0';
	//printf("%s\n", res);//
	return (res);
}

void	correct_str(char **str, int *strlen, char **mask, t_dlist **lst)
{
	int		end;
	int		start;
	int		len;
	char	*res;

	end = -1;
	start = 0;
	len = 0;
	if (!(res = ft_strdup("")))
		parser_exit(lst, mask);
	while(++end <= *strlen)
	{
		if ((*mask)[end] == '1')
			++len;
		else if (end == *strlen || (*mask)[end] == '$')
		{//{}??
			if (end == *strlen && *strlen == len)
				return ;
			if (len > 0)
				if (!stradd(&res, substr_filtered(*str + start, *mask + start, len, end - start)))
					parser_exit(lst, mask);
			if ((*mask)[start = end++] == '$')
				if (!paste_env(*str, &start, &end, &res))
					parser_exit(lst, mask);
		}
	}
	free(*mask);
	free(*str);
	*str = res;
	*strlen = ft_strlen(*str);
}