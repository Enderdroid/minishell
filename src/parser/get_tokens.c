#include "../../include/parser.h"

static void	del_last_token(t_dlist *last)
{
	if (last->prev)
		last->prev->next = NULL;
	if (((t_token *)(last->content))->str)
		free(((t_token *)(last->content))->str);
	free((t_token *)(last->content));
	free(last);
	last = NULL;
}

static int	to_lst(t_dlist **lst, char *line, int len, int *mode)
{
	t_token	*token;
	t_dlist *last;
	char	*str;

	if (!len)
		return (1);
	if (!(str = ft_substr(line, 0, len)))
		return (0);
	if (*mode == '\\')
	{
		last = ft_dlstlast(*lst);
		if (!stradd(&(((t_token *)(last->content))->str), str))
			parser_exit(lst, &line);
		((t_token *)(last->content))->len = \
							ft_strlen(((t_token *)(last->content))->str);
		*mode = 0;
		return (1);
	}
	if (!(token = malloc(sizeof(t_token *))))
		return (0);
	//printf("!%s\n", str);//
	token->str = str;
	token->len = (*mode == 'C') ? cmd_type(str) : len;
	ft_dlstadd_back(lst, ft_dlstnew(token));
	//print_list(*lst);//
	return (1);
}

static void	add_cmd(char *line, t_dlist **lst, int *start, int *end)
{
	int mode;

	mode = 'C';
	if (line[*end] == '>' && (line[*end + 1] == '>' || line[*end + 1] == '|'))
	{
		if (!to_lst(lst, &line[(*end)++], 2, &mode))
			parser_exit(lst, &line);
	}
	else if (!ft_isspace(line[*end]))
	{
		if (!to_lst(lst, &line[*end], 1, &mode))
			parser_exit(lst, &line);
	}
	//printf("s=%c,e=%c\n", line[start], line[end]);
	*start = *end + 1;
	//printf("s1=%c,e1=%c\n", line[start], line[end]);
}

static int	split_line(t_dlist **lst, char *line, int mode)
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
			if (!line[end = quote_pair(line, end)])
				return (0);
		}
		else if (ft_strchr(METACHAR, line[end]))
		{
			if (!to_lst(lst, &line[start], end - start, &mode))
				parser_exit(lst, &line);
			add_cmd(line, lst, &start, &end);
		}
	}
	if (!to_lst(lst, &line[start], end - start, &mode))
		parser_exit(lst, &line);
	return (1);
}

int			get_tokens(t_dlist **lst, char *line, int last_char)
{
	char	*tmp;
	t_dlist	*last;

	if (last_char == '\\' && !*line)
	{
		last = ft_dlstlast(*lst);
		if (!*(((t_token *)(last->content))->str + 1) && last->prev \
			&& ((t_token *)(last->prev->content))->len < 0 \
			&& *(((t_token *)(last->prev->content))->str) == '|')
		{
			del_last_token(last);
			free(line);
			parse_input('|', lst);
			return (1);
		}
		tmp = ((t_token *)(last->content))->str;
		((t_token *)(last->content))->str = \
					ft_substr(tmp, 0, ((t_token *)(last->content))->len - 1);
		free(tmp);
		if (!((t_token *)(last->content))->str)
			parser_exit(lst, &line);
		return (1);
	}
	return (split_line(lst, line, last_char));
}
//printf("len=%i\n", len);
	//printf("-%s\n", ((t_token *)((*lst)->content))->str);
	//printf("-%s\n", ((t_token *)((*lst)->next->content))->str);
