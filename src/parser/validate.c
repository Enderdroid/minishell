#include "../../include/parser.h"

static int		syntax_err_msg(const char *token, t_dlist **lst)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	write(2, "`", 1);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	g_code = 258;
	// parser_exit(lst);
	return (0);
}

static int		unclosed_q_msg(t_dlist **lst)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error: unclosed quote\n", 29);
	g_code = 258;
	// parser_exit(lst);
	return (0);
}

static int		check_token(char *str)
{
	int		i;
	t_vld	*vld;

	t_vld vld[] = { {"newline", {";", "|"} } , \
					{";", {"|"} }, \
					{">>", {">|", "<>", "newline", ">", "<", ">>", ";", "|"} }, \
					{">|", {">|", "<>", "newline", ">", "<", ">>", ";", "|"} }, \
					{"<>", {">|", "<>", "newline", ">", "<", ">>", ";", "|"} }, \
					{"|", {";"} }, \
					{">", {"<", ";", "newline", "<>", } }, \
					{"<", {"<", ";", "|", "newline", "<>"} },} ;
	i = -1;
	while (++i < 4)
	{
		int j = -1;
		if (str == vld[i].prev)
		{
		//printf("!c=%c\nstr=%c\n!!", c, vld[i].c);
			while (++j < 6)
			{	//printf("!c=%c\nstr=%c\na=%c\n!!", c, str[p], vld[i].after[j]);
				if (ft_strcmp(vld[i].after[j], str))
					return (0);
			}
		}
	}
	return (1);
}

int			validate(t_dlist **lst)
{
	t_dlist	*ptr;
	int		i;

	ptr = *lst;
	while (ptr)
	{
		if (((t_token *)(ptr->content))->len < 0)
		{
			//if (!check_token(((t_token *)(ptr->content))->str)
			///	return (syntax_err_msg(vld[i].feedback[j], lst));
		}
		ptr = ptr->next;
	}
	return (1);
}
