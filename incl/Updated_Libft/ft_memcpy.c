/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/24 20:51:56 by lweinste          #+#    #+#             */
/*   Updated: 2016/10/06 23:08:32 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char *temp;
	char *temp1;

	if (n == 0 || dst == src)
		return (dst);
	temp = (char *)dst;
	temp1 = (char *)src;
	while (--n)
		*temp++ = *temp1++;
	*temp = *temp1;
	return (dst);
}
