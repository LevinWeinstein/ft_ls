/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 21:00:16 by lweinste          #+#    #+#             */
/*   Updated: 2017/01/20 00:28:21 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	char	*temp1;
	char	*temp2;
	size_t	size;

	if (n == 0 || d == s)
		return (NULL);
	size = 0;
	temp1 = (char *)d;
	temp2 = (char *)s;
	while (size < n)
	{
		temp1[size] = temp2[size];
		if (temp1[size] == c)
			return (temp1 + size + 1);
		size++;
	}
	return (NULL);
}
