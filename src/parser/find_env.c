#include "../../include/parser.h"

char	*find_env(char *key)
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
