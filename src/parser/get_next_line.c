/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/24 17:48:14 by ttamesha          #+#    #+#             */
/*   Updated: 2020/11/13 19:02:57 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/exit.h"
#include "../../include/get_next_line.h"

static char		*ft_strjoin_part(char *s1, char *s2)
{
	char	*new;
	char	*newptr;
	size_t	len;
	char	*n;

	if (!s1 || !s2)
		return (NULL);
	n = ft_strchr(s2, '\n');
	len = n ? n - s2 + ft_strlen(s1) : ft_strlen(s1) + ft_strlen(s2);
	new = (char *)malloc(sizeof(char) * (len + 1));
	if (new == NULL)
		return (NULL);
	newptr = new;
	while (*s1)
		*newptr++ = *s1++;
	while (*s2 && *s2 != '\n')
		*newptr++ = *s2++;
	*newptr = '\0';
	return (new);
}

static int		get_line(char **line, char *src, char *rem)
{
	char *n;
	char *tmp;

	if (!*line)
		return (free_and_exit(ERRNO));
	tmp = *line;
	*line = ft_strjoin_part(tmp, src);
	free(tmp);
	if (!*line)
		return (free_and_exit(ERRNO));
	n = ft_strchr(src, '\n');
	if (n)
		ft_strcpy(rem, n + 1);
	if (!n && rem)
		ft_bzero(rem, BUFFER_SIZE);
	return (n ? 1 : 0);
}

int				get_next_line(int fd, char **line)
{
	char		buff[BUFFER_SIZE + 1];
	static char	rem[BUFFER_SIZE + 1] = {0};
	int			rd;
	int			n;

	if (!line || BUFFER_SIZE <= 0)
		return (parse_line_exit(*line, fd, ERR_DEBUG));
	*line = ft_strdup("");
	while (42)
	{
		if (*rem)
			if ((n = get_line(line, rem, rem)) != 0)
				return (n);
		while ((rd = read(fd, buff, BUFFER_SIZE)) > 0)
		{
			buff[rd] = '\0';
			if ((n = get_line(line, buff, rem)) != 0)
				return (n);
		}
		if (rd == 0 && !*rem && !(**line))
			return (rd);
		if (rd < 0)
			return (parse_line_exit(*line, fd, ERRNO));
	}
	return (parse_line_exit(*line, fd, ERR_DEBUG));
}
