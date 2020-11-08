#include "../../include/parser.h"

static int	syntax_err_msg(const char *token, t_dlist **lst)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	write(2, "`", 1);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	g_code = 258;
	free_tokens(lst);
	parse_input(0, lst);
	return (0);
}

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

static void	check_token(char *prv, char *nxt, t_dlist **lst)
{printf("in:prv=%s,nxt=%s\n", prv, nxt);
	int		i;
	int		j;
	t_vld	vld[7] = { {"newline", {";", "|", NULL} } , \
			{";", {"|", ";", NULL} }, \
			{">>", {">|", "newline", ">", "<", ">>", ";", "|", NULL} }, \
			{">|", {">|", "newline", ">", "<", ">>", ";", "|", NULL} }, \
			{"|", {";", NULL} }, \
			{">", {"<", ";", "newline", NULL} }, \
			{"<", {"<", ";", "|", "newline", ">", ">|", ">>", NULL} },} ;

	i = -1;
	while (++i < 7)
	{
		int j = -1;
		//printf("in:prv=%s,nxt=%s, prv=%s,%i\n", prv, nxt,vld[i].prv, i);
		if (!ft_strcmp(prv, vld[i].prv))
		{
			//printf("res:prv=%s,nxt=%s, prv=%s,%i\n", prv, nxt,vld[i].prv, i);
			while (vld[i].nxt[++j])
			//{	//printf("?prv=%s,nxt=%s, i=%i,j=%i\n", vld[i].prv, vld[i].nxt[j], i, j);
				if (!ft_strcmp((char *)(vld[i].nxt[j]), nxt))
					syntax_err_msg(vld[i].nxt[j], lst);
			//}
		}
	}
}

static void	check_last(char *str, int len, t_dlist **lst)
{
	char *mask;
//printf("?!\n");//
	if (len < 0)
		if (*str == '|')
			parse_input(*str, lst);
	if (str[len - 1] == '\\')
	{
		mask = tokenize_str(str, len);
		if (!mask)
			parser_exit(lst, NULL);
		if (mask[len - 1] == '0')
		{
			free(mask);
			parse_input(str[len - 1], lst);
		}
	}
	return ;
}

void		validate(t_dlist **lst, int q_closed)
{
	t_dlist	*ptr;
	t_dlist	*last;
	int		i;
	char	*nxt;
//printf("q %i\n", q_closed);//
//printf("*%s, %i\n", ((t_token *)((*lst)->content))->str, ((t_token *)((*lst)->content))->len);
	last = NULL;
	if ((ptr = *lst))
	{
		if (((t_token *)(ptr->content))->len < 0)
			check_token("newline", ((t_token *)(ptr->content))->str, lst);
		while (ptr)
		{
			if (((t_token *)(ptr->content))->len < 0 && \
				(!(ptr->next) || ((t_token *)(ptr->next->content))->len < 0))
			{
				nxt = (ptr->next) ? ((t_token *)(ptr->next->content))->str : "newline";
				check_token(((t_token *)(ptr->content))->str, nxt, lst);
			}
			if (!ptr->next)
				{last = ptr;
				printf("last=%s\n", ((t_token *)(last->content))->str);}
			ptr = ptr->next;
		}
	}
	//printf("*!%s\n", ((t_token *)(last->content))->str);
	if (!q_closed)
		unclosed_q_msg(lst);
	if (last)
		check_last(((t_token *)(last->content))->str, ((t_token *)(last->content))->len, lst);
	//printf("##%s\n", ((t_token *)((*lst)->content))->str);//
}
