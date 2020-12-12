#include "../../include/libincludes.h"


//CAN RETURN -1
int realloc_env(int new_size, int old_size)
{
	t_env **new_arr;
	int i;
	int j;

	i = -1;
	j = -1;
	if (!(new_arr = (t_env**)malloc(sizeof(t_env*) * (new_size + 1))))
		return (-1);
	while (i < old_size && i < new_size)
		new_arr[++j] = g_data->env_arr[++i];
	while (i < new_size + 1)
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
	if (!(new_str = (char*)malloc(sizeof(char) * new_size)))
		return (NULL);
	while (str[ind])
	{
		new_str[ind] = str[ind];
		++ind;
	}
	free(str);
	while(ind < new_size)
	{
		new_str[ind] = 0;
		++ind;
	}
	return (new_str);
}
