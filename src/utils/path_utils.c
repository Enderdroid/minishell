#include "../../include/libutils.h"
#include <dirent.h>


char		*add_to_folder(char *c_path, char *name, int slash)
{
	char	*buf;
	char	*ret;

	if (slash)
	{
		buf = ft_strjoin(c_path, "/");
		ret = ft_strjoin(buf, name);
		free (buf);
	}
	else
		ret = ft_strjoin(c_path, name);
	return (ret);
}

char		*rm_from_folder(char *path)
{
	int		ind;
	int		len;
	int		s_ind;
	char	*ret;

	ret = ft_strdup(path);
	ind = 0;
	while (ret[ind])
	{
		if (ret[ind] == '/')
			s_ind = ind;
		++ind;
	}
	ind = s_ind;
	while (ret[ind])
		ret[ind++] = 0;
	return (ret);
}

int			folder_search(char *path, char *name)
{
	DIR				*dir;
	struct dirent	*ent;
	int				found;

	found = 0;
	if ((dir = opendir(path)) != NULL)
	{
		while ((ent = readdir(dir)) != NULL)
			if (ft_strcmp(ent->d_name, name) == 0)
				++found;
		closedir(dir);
	}
	//else
		//ERROR
	return (found);
}

char *s_in_path(char **path_val, char *name)
{
	int i;

	i = 0;
	while (path_val[i])
	{
		if (folder_search(path_val[i], name))
			return (path_val[i]);
		++i;
	}
	return (NULL);
}
