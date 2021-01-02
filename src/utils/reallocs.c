#include "../../include/libincludes.h"
#include "../../include/libstruct.h"

int		sub_add_env(int old_size)
{
	t_env **new_arr;
	int i;

	i = -1;
	if (!(new_arr = (t_env**)malloc(sizeof(t_env*) * (old_size + 2))))
		return (-1);
	while (++i <= old_size)
		new_arr[i] = g_data->env_arr[i];
	new_arr[old_size + 1] = NULL;
	free(g_data->env_arr);
	g_data->env_arr = new_arr;
	return (0);
}

int		sub_del_env(int old_size, t_env *env)
{
	t_env **new_arr;
	int i;
	int j;

	i = 0;
	j = -1;
	if (!(new_arr = (t_env**)malloc(sizeof(t_env*) * (old_size))))
		return (-1);
	while (i <= old_size)
	{
		if (g_data->env_arr[i] != env)
			new_arr[++j] = g_data->env_arr[i];
		++i;
	}
	new_arr[old_size - 1] = NULL;
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
