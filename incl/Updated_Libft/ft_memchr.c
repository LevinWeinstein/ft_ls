/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 22:28:12 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/24 22:37:05 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*s_ptr;
	unsigned char	c_tmp;
	int				i;

	i = 0;
	c_tmp = (unsigned char)c;
	s_ptr = (unsigned char *)s;
	while (n--)
	{
		if (s_ptr[i] == c_tmp)
			return (s_ptr + i);
		i++;
	}
	return (NULL);
}
