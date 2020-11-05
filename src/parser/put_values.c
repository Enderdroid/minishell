
#include "../../include/parser.h"

static void	stradd(char **str, char *new)
{
	char *tmp;

	//if (!new || !res)
	/*{
		if (res)
		free(res);
		if (new)
		free(new);
		//ERROR
	}*/
	tmp = *str;
	*str = ft_strjoin(tmp, new);
	free(tmp);
	free(new);
	//if (!res)
		//ERROR //ret 0?
}

static char	*substr_filtered(char *str, char *mask, int len, int end)
{
	char	*res;
	int		start;
	int		i;

	res = malloc(sizeof(char) * (len + 1));
	//if (!res)
		//ERROR
	//printf("%s, %s\n", str, mask);
	i = 0;
	start = 0;
	while (start < end)
	{
		if (mask[start] == '1')
		{
			res[i] = str[start];
			++i;
		}
		++start;
	}
	res[i] = '\0';
	//printf("%s\n", res);//
	return (res);
}

static char	*find_env(char *key)
{
	char	*value;
	int		i;

	i = -1;
	value = NULL;
	while (env[++i].key)//size?
	{
		if (ft_strcmp(env[i].key, key) == 0)
		{
			value = ft_strdup(env[i].value);
			break ;
		}
	}
	if (!value)
		value = ft_strdup("");
	free(key);
	return (value);
}

static void	put_env(char *str, int *start, int *end, char **res)
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
			while(ft_isalpha(str[*end]) || ft_isdigit(str[*end]) || str[*end] == '_')
				++(*end);
			new = find_env(ft_substr(str, *start + 1, *end - *start - 1));
		} //if(!new)?
		stradd(res, new);//if (!stradd/!res)?//ERROR
		*start = *end;
	}
}

void	correct_str(char **str, int strlen, char *mask)
{
	int		end;
	int		start;
	int		len;
	char	*res;

	end = -1;
	start = 0;
	len = 0;
	res = ft_strdup("");
	//if (!res)
		//ERROR
	while(++end <= strlen)
	{
		if (mask[end] == '1')
			++len;
		else if (end == strlen || mask[end] == '2')
		{//{}??
			if (len > 0)
				stradd(&res, substr_filtered(*str + start, mask + start, len, end - start)); //if(!stradd/!res)?
			if (mask[start = end++] == '2')
				put_env(*str, &start, &end, &res); //if(!put_env)?
		}
	}
	free(mask);
	//if (!res)? //free (envs lst) and exit
	free(*str);
	*str = res;
}