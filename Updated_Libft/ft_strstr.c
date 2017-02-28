/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 09:14:40 by lweinste          #+#    #+#             */
/*   Updated: 2016/10/06 23:15:01 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *big, const char *little)
{
	const char	*b;
	const char	*l;

	b = big;
	l = little;
	if (*l == '\0')
		return ((char *)big);
	while (*big)
	{
		l = little;
		l = ft_strdup(little);
		while (*l && (*l == *b))
		{
			b++;
			l++;
		}
		if (!*l)
			return ((char *)big);
		big++;
		b = big;
	}
	return (NULL);
}
