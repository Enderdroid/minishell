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
//	else

	return (found);
}

char *s_in_path(char *name)
{
	int i;
	char **path_content;
	char *path;
	t_env *l_path;

	if (!(l_path = find_env_b("PATH")))
		return (NULL);
	path_content = ft_split(l_path->value, ':');
	if (!path_content)
		free_and_exit(ERRNO);
	i = 0;
	while (path_content[i])
	{
		if (folder_search(path_content[i], name))
		{
			path = ft_strjoin(path_content[i], "/");//defend
			free_arr(path_content);
			return (path);
		}
		++i;
	}
	free_arr(path_content);
	return (NULL);
}
