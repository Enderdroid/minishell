/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   countdigits.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttamesha <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 20:11:47 by ttamesha          #+#    #+#             */
/*   Updated: 2020/10/01 20:12:18 by ttamesha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	countdigits(int n)
{
	int count;

	count = 1;
	while (n / 10 != 0)
	{
		count++;
		n /= 10;
	}
	return (count);
}