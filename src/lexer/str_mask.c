#include "../../include/lexer.h"

static void process_slash(char *str, char *mask, int *i)
{
	mask[*i] = '0';
	if (str[++(*i)])
		mask[*i] = '1';
}

static void process_single_quote(char *str, char *mask, int *i)
{
	mask[*i] = '0';
	while (str[++(*i)] && str[*i] != '\'')
		mask[*i] = '1';
	if (str[*i])
		mask[*i] = '0';
}

static void check_dollar(char *str, char *mask, int i, int q)
{
	if (str[i] == '$' && !ft_strchr(" ~:/.,^+=\\\%\0", str[i + 1]) \
		&& !(str[i + 1] == '\"' && q))
		mask[i] = '$';
	else
		mask[i] = '1';
}

char	*str_mask(char *str, int len)
{
	char	*mask;
	int		i;
	int		q;

	i = 0;
	q = 0;
	if (!(mask = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	while (i < len)
	{
		if (str[i] == '\"')
		{
			mask[i] = '0';
			q = (q) ? 0 : 1;
		}
		else if (str[i] == '\'' && !q)
			process_single_quote(str, mask, &i);
		else if (str[i] == '\\' && (!q || ft_strchr("$\"\\\0", str[i + 1])))
			process_slash(str, mask, &i);
		else
			check_dollar(str, mask, i, q);
		++i;
	}
	mask[len] = '\0';
	return (mask);
}
