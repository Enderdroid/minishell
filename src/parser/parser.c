/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/10/30 23:00:22 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

char	*add_str(char *line, char *res, int start, int end)
{
	char *new;
	char *tmp;

	new = ft_substr(line, start, end - start);
	//if (!new)
	//ERROR
	tmp = res;
	res = ft_strjoin(tmp, new);
	//if (!res)
	//ERROR
	free(tmp);
	free(new);
}

//$> synt err
//$% ?????
//$- $0 $# $!
//$~ $=
void	to_lst(char *str, int id) //int len?
{
	t_token token;
	t_dlist *lst;//where to create lst?

	//if (!str)
	//ERROR
	token.id = id;
	token.str = str;
	//token.len = len;
	ft_dlstadd_back(&lst, ft_dlstnew(&token));
}

char	*parse_quotes(char *line, t_env env)
{
	int end;
	int start;
	char *str;
	char *new;
	char *tmp;

	end = 0;
	start = 0;
	while(line[end++]) //len
	{
		if (line[end] == '\'' || line[end] == '\"' && esc_seq(line, end)) // \\ line[end] == \0
		{
			str = ft_substr(line, start, end - 1 - start); // check \$
			//if (!str) //ERROR
			start = end + 1;
			while (line[end] == '\'' || line[end] == '\"' && esc_seq(line, end))
			{
				end = quote_end(line, end);
				new = ft_substr(line, start, end - start); // check q type if " convert \ $
				tmp = str;
				str = ft_strjoin(tmp, new);
				//if (!str)
				free(tmp);
				free(new);
				start = ++end;
			}
		//add last part if no len used
		//add to lst (str); // change str in list: free(line/token.str); token.str = str;
		}
	}
	return (str);
}

int	parse_line(char *line, t_env *env)
{
	int start;
	int end;

	if (input_is_valid(line)) //do it via list after parsing
	{
		end = 0;
		start = 0;
		while(line[end++])
		{
			if (line[end] == '\'' || line[end] == '\"' && esc_seq(line, end))
			{
				end = quote_end(line, end);
				start = ++end;
			}
			else if (ft_strchr(METACHAR, line[end]) && esc_seq(line, end))
			{//if (line[end] == ';') cmd end, validate and send 
				if (end - 1 - start > 0)
					ft_substr(line, start, end - 1 - start); // add to lst, check quotes \ $ //malloc protection in next func - ok with errno?
				if (line[end] == '>' && line[end + 1] == line[end])
					ft_substr(line, end++, 2); //add to lst as cmd
				else if (line[end] == '>' && line[end + 1] == '|')
					ft_substr(line, end++, 2); //add to lst as cmd
				else if (!ft_isspace(line[end]))
					ft_substr(line, end, 1); //add to lst as cmd
				start = ++end;
			}
		}
		return (1); //if line is empty?
	}
	return (0);
}

void			parse_input(t_env *env)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(STDIN_FILENO, &line)) != 0 || *line)
	{
		if (!parse_line(line, env))
		{
			//free_and_exit();
		}
	}
	if (ret == 0)
	{
		//free(line);
		//free_and_exit();
	}
	free(line);
}
