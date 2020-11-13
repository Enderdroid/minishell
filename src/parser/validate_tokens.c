
#include "../../include/parser.h"

static int	unclosed_q_msg(t_dlist **lst)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error: unclosed quote\n", 29);
	g_code = 258;
	if (*lst)
		free_tokens(lst);
	parse_input(0, lst);
	return (0);
}

static void	check_last(t_token *token, t_dlist **lst, t_dlist *prv)
{
	char *tmp;
//printf("?!\n");//
	if (token->len == C_PIPE)
		parse_input('|', lst);
	if (token->str[token->len - 1] == '\\')
	{
		if (!(tmp = str_mask(token->str, token->len)))
			parser_exit(lst, NULL);
		if (tmp[token->len - 1] == '0')
		{
			free(tmp);
			parse_input('\\', lst);
		}
		free(tmp);
	}
}

void		validate_tokens(t_dlist **lst, int q_closed)
{
	t_dlist	*last;
//printf("q %i\n", q_closed);// //printf("*%s, %i\n", ((t_token *)((*lst)->content))->str, ((t_token *)((*lst)->content))->len);
	last = NULL;
	check_syntax_error(lst, &last);
	if (!q_closed)
		unclosed_q_msg(lst);
	if (last)
		check_last((t_token *)(last->content), lst, last->prev);
	//printf("##%s\n", ((t_token *)((*lst)->content))->str);//
}
