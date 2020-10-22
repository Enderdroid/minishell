#include "../../include/libutils.h"
#include <dirent.h>


void		add_folder(char *c_path, char *name)
{

}

char		*s_in_path(/*u_env, */char *name)
{

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
