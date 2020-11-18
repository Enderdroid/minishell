#include "../../include/lexer.h"

static int	cmd_type(char *cmd)
{
	if (*cmd == '|')
		return (C_PIPE);
	if (*cmd == '>')
	{
		if (*(cmd + 1) == '>')
			return (C_RDR_R_DBL);
		return (C_RDR_R);
	}
	if (*cmd == '<')
		return (C_RDR_L);
	if (*cmd == ';')
		return (C_END);
	return (-1);
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
	if (!(token = (t_token *)malloc(sizeof(t_token))))
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

static int	quote_pair(char *input, int i)
{
	char quote;

	quote = input[i];
	while (input[++i])
	{
		if (input[i] == quote)
			break ;
		else if (input[i] == '\\' && quote == '\"' && input[i + 1])
			++i;
	}
	return (i);
}

int			split_line(t_dlist **lst, char *line, int mode)
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