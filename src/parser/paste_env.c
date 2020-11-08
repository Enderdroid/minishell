
#include "../../include/parser.h"

static char	*find_env(char *key)
{
	char	*value;
	int		i;

	if (!key)
		return (NULL);
	i = -1;
	value = NULL;
	while (data->env_arr[++i].key)
	{
		//printf("%s\n", env[i].key);//
		if (ft_strcmp(data->env_arr[i].key, key) == 0)
		{
			value = ft_strdup(data->env_arr[i].value);
			if (!value)
				return (NULL);
			break ;
		}
	}
	if (!value)
		value = ft_strdup("");
	free(key);
	return (value);
}

int			paste_env(char *str, int *start, int *end, char **res)
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
		}
		if (!stradd(res, new))
			return (0);
		*start = *end;
	}
	return (1);
}
