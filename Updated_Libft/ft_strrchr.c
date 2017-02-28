/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchar.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 08:58:33 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/25 09:12:24 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	char	check;

	i = ft_strlen(s);
	check = (char)c;
	while (*s != '\0')
		s++;
	while (i >= 0)
	{
		if (*s == check)
			return ((char *)s);
		s--;
		i--;
	}
	return (NULL);
}
