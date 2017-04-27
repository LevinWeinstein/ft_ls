/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 10:17:23 by lweinste          #+#    #+#             */
/*   Updated: 2016/10/06 23:16:01 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t lsize;

	if (*little == '\0')
		return ((char *)big);
	lsize = ft_strlen(little);
	while (*big != '\0' && lsize <= len)
	{
		if (ft_strncmp(big, little, lsize) == 0)
			return ((char *)big);
		big++;
		len--;
	}
	return (NULL);
}
