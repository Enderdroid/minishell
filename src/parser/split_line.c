#include "../../include/parser.h"

static int	join_to_last(t_dlist *last, char *str)
{
	char	*tmp;

	tmp = ((t_token *)(last->content))->str;
	((t_token *)(last->content))->str = ft_strjoin(tmp, str);
	free(tmp);
	free(str);
	if (!((t_token *)(last->content))->str)
		return (0);
	((t_token *)(last->content))->len = ft_strlen(((t_token *)(last->content))->str);
	return (1);
}

static int	to_lst(t_dlist **lst, char *line, int len, int *mode)
{
	t_token	*token;
	char	*str;

	if (!len)
		return (1);
	str = ft_substr(line, 0, len);
	if (!str)
		return (0);
	if (*mode == '\\')
	{
		if (!join_to_last(ft_dlstlast(*lst), str))
			return (0);
		*mode = 0;
		return (1);
	}
	token = malloc(sizeof(t_token *));
	if (!token)
		return (0);
	printf("!%s\n", str);//
	token->str = str;
	token->len = (*mode == 'c') ? -1 : len;
	//if (*lst)
	//	printf("*!%s\n", ((t_token *)((*lst)->content))->str);
	ft_dlstadd_back(lst, ft_dlstnew(token));
	printf("#head=%s,%i\n", ((t_token *)((*lst)->content))->str, ((t_token *)((*lst)->content))->len);//
	return (1);
}

static void	add_cmd(char *line, t_dlist **lst, int *start, int *end)
{
	int mode;

	mode = 'c';
	if (line[*end] == '>' && (line[*end + 1] == '>' || line[*end + 1] == '|'))
	{
		if (!to_lst(lst, &line[(*end)++], 2, &mode))
			parser_exit(lst, &line); //add to lst as cmd
	}
	else if (!ft_isspace(line[*end]))
	{
		if (!to_lst(lst, &line[*end], 1, &mode))
			parser_exit(lst, &line); //add to lst as cmd
	}
	//printf("s=%c,e=%c\n", line[start], line[end]);
	*start = *end + 1;
	//printf("s1=%c,e1=%c\n", line[start], line[end]);
}

/*static void	join_line(char **line, t_dlist **lst)
{
	t_dlist *last;
	char	*tmp;

	last = ft_dlstlast(*lst);
	tmp = *line;
	*line = ft_strjoin(((t_token *)(last->content))->str, tmp);
	if (!*line)
		parser_exit(lst, NULL);
	free(tmp);
	free(((t_token *)(last->content))->str);
	free((t_token *)(last->content));
	if (last->prev)
		last->prev->next = NULL;
	else
		{free(*lst);
			*lst = NULL;
		}
	//free(last);
	last = NULL;
	printf("?%s\n", *line);
}*/
int			empty_after_backslash(t_dlist **lst, char *line, int last_char)
{
	char *whitespace;

	if (last_char == '\\' && !*line)
	{
		whitespace = ft_strdup(" ");
		if (!whitespace)
			parser_exit(lst, &line);
		if (!join_to_last(ft_dlstlast(*lst), whitespace))
			parser_exit(lst, &line);
		return (1);
	}
	return (0);
}

int			split_line(char *line, t_dlist **lst, int mode)
{
	int start;
	int end;

	end = (mode  == '\\') ? 0 : -1;
	start = 0;
	while(line[++end])
	{
		if (line[end] == '\\' && line[end + 1])
			++end;
		else if ((line[end] == '\'' || line[end] == '\"'))
		{
			if (!line[end = quote_pair(line, end)])//--end;
				return (0); //unclosed quote//printf("s=%c,e=%c,%i,%i\n", line[start], line[end], start, end);
		}
		else if (ft_strchr(METACHAR, line[end]))
		{
			if (!to_lst(lst, &line[start], end - start, &mode))
				parser_exit(lst, &line); //ft_substr(line, start, len), len, &mode); // add to lst, check quotes \ $ //malloc protection in next func - ok with errno?
			add_cmd(line, lst, &start, &end);
		}
	}
	if (!to_lst(lst, &line[start], end - start, &mode))
		parser_exit(lst, &line); //if (!to_lst) //free_and_exit(lst)
	return (1);
}
//printf("len=%i\n", len);
	//printf("-%s\n", ((t_token *)((*lst)->content))->str);
	//printf("-%s\n", ((t_token *)((*lst)->next->content))->str);