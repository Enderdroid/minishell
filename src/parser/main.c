#include "../../include/parser.h"

int	main(int ac, char **av, char** envp)
{
	t_dlist *lst;

	(void)ac;
	(void)av;

	init_data(envp);
	lst = NULL;
	while(42)
		parse_input(0, &lst);

	//char *str = "c   ;";
	//input_is_valid(str);
	/*
	i = -1;
	while (++i < size)
	{
		printf("%s\n", (env[i]).key);
		printf("%s\n", (env[i]).value);
		printf("%s\n", *((env[i]).link));
	}
	printf("%s\n", (path_env.l_old_pwd->key));
	printf("%s\n", (path_env.l_old_pwd->value));
	printf("%s\n", (path_env.l_pwd->key));
	printf("%s\n", (path_env.l_pwd->value));
	printf("%s\n", *(path_env.path_content));
	*/
}
