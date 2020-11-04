#include "../../include/parser.h"

static int	no_slash_len(char *line)
{
	int i;

	i = 0;
	while (*line)
	{
		if (*line == '\\')
		{
			if (*(++line))
			{
				++line;
				++i;
			}
		}
		else
		{
			++line;
			++i;
		}
	}
	return (i);
}

char			*check_slash(char *line)
{
	char *res;
	int i;
	int j;

	res = malloc(sizeof(char) * no_slash_len(line));
	//if (!res)
	//ERROR
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
	free(line);
	return (res);
}

//$> synt err
//$% ?????
//$- $0 $# $!
//$~ $=
char	*change_dollars(char *line, t_env *env)
{
	int		i;
	int		start;
	char	*new;
	char	*res;
	char	*tmp;

	i = -1;
	start = 0;
	res = ft_strdup("");
	//if (!res) ERROR
	while(line[++i]) //len? // add last part
	{
		if (line[i] == '$' && esc_seq(line, i++))
		{
			//{}??
			if (!ft_strchr(METACHAR, line[i]) && !ft_strchr("\0 ~:/.,^+=\\\%", line[i]))
			{
				new = ft_substr(line, start, i - 1 - start);
				tmp = res;
				res = ft_strjoin(tmp, new);
				//if (!res) ERROR
				free(tmp);
				free(new);
				start = i;

				if (!ft_isalpha(line[i]) && line[i] != '_')
					start = ++i;
				else
				{
					if (line[i] == '?')
						new = ft_itoa(g_code);//take last return value
					else
					{
						while(ft_isalpha(line[i]) || ft_isdigit(line[i]) || line[i] == '_')
							++i;
						new = find_env(ft_substr(line, start, i - start), env);
					}
					tmp = res;
					res = ft_strjoin(tmp, new);
					free(tmp);
					free(new);
					start = i;
				}
			}
		}
	}
	free(line);
	return (res);
}

char	*parse_quotes(char *line, t_env env)
{
	int		end;
	int		start;
	char	*str;
	char	*new;
	char	*tmp;

	end = 0;
	start = 0;
	while(line[end]) //end < len
	{
		if ((line[end] == '\'' || line[end] == '\"') && esc_seq(line, end)) // \\ line[end] == \0
		{
			str = ft_substr(line, start, end - start); // check \$
			//if (!str) //ERROR
			start = end + 1;
			while ((line[end] == '\'' || line[end] == '\"') && esc_seq(line, end))
			{
				end = quote_pair(line, end);
				new = ft_substr(line, start, end - start); // check q type if " convert \ $
				tmp = str;
				str = ft_strjoin(tmp, new);
				//if (!str) //ERROR
				free(tmp);
				free(new);
				start = ++end;
			}
		//change str in list: free(line/token.str); token.str = str;//add last part if no len used
		}
		else
			++end;
	}
	return (str);
}