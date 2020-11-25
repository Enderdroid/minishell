#include "../../include/libincludes.h"

int	realloc_env(int new_size, int old_size)
{
	t_env	**new_arr;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_arr = (t_env**)malloc(sizeof(t_env*) * new_size);
	while (i < old_size)
		if (g_data->env_arr[i])
			new_arr[j++] = g_data->env_arr[i];
	while (i < new_size)
		new_arr[i++] = NULL;
	free(g_data->env_arr);
	g_data->env_arr = new_arr;
	return (0);
}

char	*ft_realloc(char *str, int new_size)
{
	char *new_str;
	int		ind;

	ind = 0;
	new_str = (char*)malloc(sizeof(char) * new_size);
	while (str[ind])
	{
		new_str[ind] = str[ind]; //new_str[ind] = str[ind++];
		++ind;
	}
	free(str);
	while (ind < new_size)
		new_str[ind] = 0;
	return (new_str);
}
