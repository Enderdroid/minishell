/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/19 15:59:48 by ttamesha          #+#    #+#             */
/*   Updated: 2020/10/29 23:02:15 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/parser.h"

char			*unshield(char *line) // take size == 3rd arg of substr
{
	char *res;
	int i;
	int j;
//if (*str == '$' && )
//malloc protection for join and substr!
	i = ft_strlen(line);
	res = malloc(sizeof(char) * i); //ft_calloc
	//if (!res)
	//ERROR
	ft_bzero(res, i);
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i] == '\\')
		{
		//	if (line[i + 1] == '\0')
			//ask for continue input
			res[j++] = line[++i];
		}
		else
			res[j++] = line[i++];
	}
/*
	char *res;
	int end;
	int start;
	char *str;
	char *tmp;

	end = -1;
	start = 0;
	res = NULL;
	while (line[++end])
	{
		if (line[end] == '\\')
		str = ft_substr(str, start, end - 1 - start);
		tmp = res;
		res = ft_strjoin(tmp, str);
		free(str);
		if (tmp)
			free(tmp);
		start = ++end;
	}
	//if (line[end -1] == '\\')
		//ask for continue input
	str = ft_substr(str, start, end - 1 - start);
	tmp = res;
	res = ft_strjoin(tmp, str);
	free(str);
	if (tmp)
		free(tmp);*/
	free(line);
	return (res);
}

/*
//don't know what to do "$blabla\$blst" '$'
char *change_dollars(char *line)
{
	int i;

	i = -1;
	while(line[++i])
	{
		if (line[i] == '$' && not_shielded(line, i))
		{
			//{}??
			if (line[i + 1] == '_')
			else if (line[i + 1] == ' ')
			else if (!is_alpha(line[i + 1])
				//empty;???
			while(ft_isalpha(line[++i]))
		}
	}
}
*/

void to_lst(char *str, int id)
{
	t_token token;
	t_dlist *lst;//where to create lst?

	token.id = id;
	token.str = str;
	ft_dlstadd_back(&lst, ft_dlstnew(&token));
}

int				parse_line(char *line)
{
	int start;
	int end;
	char *tmp;
	char *str;
	char *inquote;
//malloc protection for join and substr!
	if (input_is_valid(line))
	{
		end = -1;
		start = 0;
		while(line[++end])
		{
			if (line[end] == '\'' || line[end] == '\"' && not_shielded(line, end))
			{
				str = ft_substr(line, start, end - 1 - start); // check \$
				start = end + 1;
				while (line[end] == '\'' || line[end] == '\"' && not_shielded(line, end))
				{
					end = quote_end(line, end);
					inquote = ft_substr(line, start, end - 1 - start); // check q type if " convert \ $
					tmp = str;
					str = ft_strjoin(tmp, inquote);
					free(tmp);
					free(inquote);
					start = ++end;
				}
			//add to lst (str);
			}
			if (ft_strchr(METACHAR, line[end]) && not_shielded(line, end))
			{
				if (end - 1 - start > 0)
					ft_substr(line, start, end - 1 - start); // check \ $ && add to lst
				if (line[end] == '>' && line[end + 1] == line[end])
					ft_substr(line, end++, 2); //add to lst as cmd
				else if (!ft_isspace(line[end]))
					ft_substr(line, end, 1); //add to lst as cmd
				start = ++end;
			}
		}
		return (1);
	}
	return (0);
}

void			parse_input(void)
{
	int		ret;
	char	*line;

	while ((ret = get_next_line(STDIN_FILENO, &line)) != 0 || *line)
	{
		if (!parse_line(line))
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
