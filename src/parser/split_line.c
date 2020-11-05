#include "../../include/parser.h"

static void	to_lst(t_dlist **lst, char *str, int len)
{
	t_token *token;

	//if (!str)
	//ERROR
	token = malloc(sizeof(t_token *));
	//if (!token)
	//ERROR
	printf("!%s\n", str);//
	token->str = str;
	token->len = len;
	//if (*lst)
	//	printf("*!%s\n", ((t_token *)((*lst)->content))->str);
	ft_dlstadd_back(lst, ft_dlstnew(token));
	//printf("#%s\n", ((t_token *)((*lst)->content))->str);
}
void	split_line(char *line, t_dlist **lst)
{
	int start;
	int end;
	int len;
	int q;

	end = -1;
	start = 0;
	q = 0;
	while(line[++end])
	{
		if (line[end] == '\\' && line[end + 1])
			++end;
		else if ((line[end] == '\'' || line[end] == '\"'))
		{
			if (!line[end = quote_pair(line, end)])
				--end; //unclosed quote
			//printf("s=%c,e=%c,%i,%i\n", line[start], line[end], start, end);
		}
		else if (ft_strchr(METACHAR, line[end]))
		{
			if ((len = end - start) > 0)
			{	to_lst(lst, ft_substr(line, start, len), len); // add to lst, check quotes \ $ //malloc protection in next func - ok with errno?
				//printf("len=%i\n", len);
				//printf("?%s\n", ((t_token *)((*lst)->content))->str);
			}
			if (line[end] == '>' && (line[end + 1] == '>' || line[end + 1] == '|'))
				to_lst(lst, ft_substr(line, end++, 2), -1); //add to lst as cmd
			else if (!ft_isspace(line[end]))
				to_lst(lst, ft_substr(line, end, 1), -1); //add to lst as cmd
			//printf("s=%c,e=%c\n", line[start], line[end]);
			start = end + 1;
			//printf("s1=%c,e1=%c\n", line[start], line[end]);
		}
	}
	if ((len = end - start) > 0)
		to_lst(lst, ft_substr(line, start, len), len); // add to lst, check quotes \ $ //malloc protection in next func - ok with errno?
	//printf("len=%i\n", len);
	//printf("-%s\n", ((t_token *)((*lst)->content))->str);
	//printf("-%s\n", ((t_token *)((*lst)->next->content))->str);
}