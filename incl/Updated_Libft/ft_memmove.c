/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 21:42:33 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/26 17:16:21 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *d, const void *s, size_t n)
{
	char *temp;
	char *temp1;

	if (d < s)
		return (ft_memcpy(d, s, n));
	if (d > s)
	{
		temp = (char *)d;
		temp1 = (char *)s;
		while (n--)
		{
			temp[n] = temp1[n];
		}
	}
	return (d);
}
