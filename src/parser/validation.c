#include "../../include/parser.h"

static int		syntax_err_msg(const char *token)
{
	write(2, "minishell: ", 11);
	write(2, "syntax error near unexpected token ", 35);
	write(2, "`", 1);
	write(2, token, ft_strlen(token));
	write(2, "'\n", 2);
	return (0);
}

static int		quote_end(char *input, int i, char quote)
{
	while (input[++i])
	{
		if (input[i] == quote && (input[i - 1] != '\\' && i > 0))
			break;
	}
	return (i);
}

static int		check_token(char c, int p, char *str)
{
	int		fst;
	int		i;
	//t_vld	*vld;

	/*while ((fst = p - 1) >= 0)
	{
		if (str[fst] == ' ')
			--fst;
	}
	if (!fst)
	{
		fst = 7;}*/
		t_vld	vld[] = { {';', ";|><~\0", {";;", ";", ";", ";", ";", ";"} } , \
					{'|', "|;><~\0", {"||", "|", "|", "|", "|", "|"} }, \
					{'>', "<;|\0\0\0", {"newline", "<", ";", "newline"} }, \
					{'<', ">;|\0\0\0", {"newline", "<", ";", "newline"} }, } ;

	//printf("---%c\n %s\n", vld[1].after[1], vld[1].feedback[1]);
//}

	/*else
	{
		fst = 3;
		t_vld	vld[] = { {';', ";|><", {";;", ";|", "newline", "newline"} } , \
				{'|', ";><", {";", "newline", "newline"} }, \
				{'>', "\n<;|", {"newline", "<", ";", "newline"} }, \
				{'<', "\n>;|", {"newline", "<", ";", "newline"} }, } ;
	}*/
	i = -1;
	while (++i < 4)
	{
		int j = -1;
		if (c == vld[i].c)
		{
		printf("!c=%c\nstr=%c\n!!", c, vld[i].c);
			while (++j < 6)
			//{	//printf("!c=%c\nstr=%c\na=%c\n!!", c, str[p], vld[i].after[j]);
				if (vld[i].after[j] == str[p])
					return (syntax_err_msg(vld[i].feedback[j]));
			//}
		}
	}
	return (1);
}

int				input_is_valid(char *input)
{
	int		i;
	char	c;

	i = -1;
	while (input[++i])
	{
		if ((input[i] == '\'' || input[i] == '\"') && (input[i - 1] != '\\' && i > 0))
			i = quote_end(input, i, input[i]);
		else if (ft_strchr(";&|><", input[i]))
		{
			c = input[i++];
			while (input[i] == ' ')
				++i;
			if (!check_token(c, i, input))
				return(0);
		}
	}
	return(1);
}
