/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/02 23:36:39 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/02 23:36:40 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libincludes.h"
#include <dirent.h>

int		folder_search(char *path, char *name)
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

char	*s_in_path(char *name, t_env *l_path)
{
	int		i;
	char	**path_content;
	char	*path;

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
