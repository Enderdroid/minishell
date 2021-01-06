/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   correct_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 22:00:05 by ttamesha          #+#    #+#             */
/*   Updated: 2021/01/06 22:00:22 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/lexer.h"

void		correct_tokens(t_dlist *lst)
{
	t_dlist	*lptr;
	char	*newstr;

	lptr = lst;
	while (lptr)
	{
		if (((t_token *)(lptr->content))->len == C_END)
			return ;
		if (((t_token *)(lptr->content))->len > 0)
		{
			if ((newstr = corrected_str((t_token *)(lptr->content))))
			{
				free(((t_token *)(lptr->content))->str);
				((t_token *)(lptr->content))->str = newstr;
			}
		}
		lptr = lptr->next;
	}
}
