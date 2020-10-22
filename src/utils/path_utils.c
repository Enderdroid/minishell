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

char		*s_in_path(char **path, char *name)
{
	int		i;

	i = 0;
	while(path[i])
		if (folder_search(path[i], name))
			return(add_to_folder(path[i], name, 1));
	return (NULL);
}

int			folder_search(char *path, char *name)
{
	DIR *dir;
	struct dirent *ent;
	int		found;

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
