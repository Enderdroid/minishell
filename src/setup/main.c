/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 01:50:22 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/22 23:12:36 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/parserstruct.h"

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	init_data(envp);

	while(42)
	{
		handle_signals();
		parse_input(0);
	}
	//free_data();//


	/*int i = 0;
	while (g_data->env_arr[i])
	{
		printf("%s\n", g_data->env_arr[i]->key);
		printf("%s\n", g_data->env_arr[i]->value);
		printf("%s\n", *(g_data->env_arr[i]->link));
		printf("\n\n%i\n\n", i);
		++i;
	}
	printf("%s\n", (g_data->u_env->l_old_pwd->key));
	printf("%s\n", (g_data->u_env->l_old_pwd->value));
	printf("%s\n", (g_data->u_env->l_pwd->key));
	printf("%s\n", (g_data->u_env->l_pwd->value));
	//printf("%s\n", *(g_data->u_env->path_content));*/

}
