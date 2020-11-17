
#include "../../include/parser.h"

void	fill_name_path(char *str, t_exec *exec, char **name, t_dlist **lst)
{
	char *s;

	if (*(str + 1) == '/')
	{
		if (*str == '~')
			if (!(exec->path = find_env(ft_strdup("HOME"))))
				parser_exit(lst, NULL);
		if (*str == '.')
			if (!(exec->path = find_env(ft_strdup("PWD"))))
				parser_exit(lst, NULL);
	}
	//s = ft_strrchr(str, '/');
	exec->name = (s = ft_strrchr(str, '/')) ? ft_strdup((s + 1)) : ft_strdup(str);
	if (!exec->name)
		parser_exit(lst, NULL);
	if (!(*name = ft_strdup(exec->name))) //argv[0]
		parser_exit(lst, NULL);
	if (s)
	{
		if (exec->path)
			stradd(&(exec->path), ft_substr(str, 1, s - str));
		else
			exec->path = ft_substr(str, 0, s - str);
		if (!exec->path)
			parser_exit(lst, NULL);
	}
	printf("name = %s\n", exec->name);//
	printf("path = %s\n",exec->path);//
}
