#include "../../include/parser.h"

char	*find_env(char *key)
{
	char	*value;
	int		i;

	if (!key)
		return (NULL);
	i = -1;
	value = NULL;
	//printf("%s\n", (data->env_arr)[1]->key);
	while (data->env_arr[++i])
	{
		//printf("%s, %i\n", data->env_arr[i]->key, i);//
		if (ft_strcmp(data->env_arr[i]->key, key) == 0)
		{
			value = ft_strdup(data->env_arr[i]->value);
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
