
#include "../../include/lexer.h"

static int	paste_env(char *str, int *start, int *end, char **res)
{
	char *new;

	if (!ft_isalpha(str[*end]) && str[*end] != '_' && str[*end] != '?')
		*start = ++(*end);
	else
	{
		if (str[*end] == '?')
		{
			new = ft_itoa(g_code);//take last return value
			++(*end);
		}
		else
		{
			while (ft_isalpha(str[*end]) || \
					ft_isdigit(str[*end]) || str[*end] == '_')
				++(*end);
			new = find_env(ft_substr(str, *start + 1, *end - *start - 1));
		}
		if (!stradd(res, new))
			return (0);
		*start = *end;
	}
	return (1);
}

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

static void	correct_str(t_token *token, char **res, char **mask, t_dlist **lst)
{
	int		end;
	int		start;
	int		len;

	end = -1;
	start = 0;
	len = 0;
	while (++end <= token->len)
	{
		if ((*mask)[end] == '1')
			++len;
		else if (end == token->len || (*mask)[end] == '$')
		{
			if (end == token->len && token->len == len)
			{
				free(*res);
				*res = NULL;
				return ;
			}
			if (len > 0)
				if (!stradd(res, substr_filtered(token->str + start, \
							*mask + start, len, end - start)))
					parser_exit(lst, mask);
			if ((*mask)[start = end++] == '$')
				if (!paste_env(token->str, &start, &end, res))
					parser_exit(lst, mask);
		}
	}
}

char		*corrected_str(t_dlist **lst, t_token *token)
{
	char *mask;
	char *res;

	if (!(mask = str_mask(token->str, token->len)))
		parser_exit(lst, NULL);
	if (!(res = ft_strdup("")))
		parser_exit(lst, &mask);
	correct_str(token, &res, &mask, lst);
	free(mask);
	return (res);
}
