#include "../../include/parser.h"

int	main(int ac, char **av, char** envp)
{
	t_dlist *lst;
	t_data *data;
	(void)ac;
	(void)av;

	//data = NULL;
	init_data(envp);

	lst = NULL;
	while(42)
		parse_input(0, &lst);

	/*int i = 0;
	while (data->env_arr[i])
	{
		printf("%s\n", data->env_arr[i]->key);
		printf("%s\n", data->env_arr[i]->value);
		printf("%s\n", *(data->env_arr[i]->link));
		printf("\n\n%i\n\n", i);
		++i;
	}
	printf("%s\n", (data->u_env->l_old_pwd->key));
	printf("%s\n", (data->u_env->l_old_pwd->value));
	printf("%s\n", (data->u_env->l_pwd->key));
	printf("%s\n", (data->u_env->l_pwd->value));
	//printf("%s\n", *(data->u_env->path_content));*/

}
