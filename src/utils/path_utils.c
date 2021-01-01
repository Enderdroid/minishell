#include "../../include/libincludes.h"
#include <dirent.h>
#include "../../include/error.h"

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
	return (found);
}

static char	*check_path()
{
	char	*path;

	path = ft_strdup("");
	if (!path)
		free_and_exit(ERRNO);
	return (path);
}

char		*s_in_path(char *name)
{
	int		i;
	char	**path_content;
	char	*path;
	t_env	*l_path;

	if (!(l_path = find_env_b("PATH")) || !l_path->value || !l_path->value[0])
		return (check_path());
	if (!(path_content = ft_split(l_path->value, ':')))
		free_and_exit(ERRNO);
	i = 0;
	while (path_content[i])
	{
		if (folder_search(path_content[i], name))
		{
			path = ft_strjoin(path_content[i], "/");
			free_arr(path_content);
			if (!path)
				free_and_exit(ERRNO);
			return (path);
		}
		++i;
	}
	free_arr(path_content);
	return (NULL);
}
