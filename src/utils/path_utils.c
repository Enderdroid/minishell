#include "../../include/libincludes.h"
#include <dirent.h>

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
			{
				++found;
				if (ent->d_type == DT_DIR)
					++found;
			}
		closedir(dir);
	}
	else
		free_and_exit(ERRNO);
	return (found);
}

char *s_in_path(char **path_val, char *name)
{
	int i;

	i = 0;
	while (path_val[i])
	{
		if (folder_search(path_val[i], name))
			return (ft_strjoin(path_val[i], "/"));
		++i;
	}
	return (NULL);
}
