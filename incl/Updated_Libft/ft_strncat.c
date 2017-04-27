/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 06:25:09 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/26 15:39:23 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strncat(char *s1, const char *s2, size_t size)
{
	size_t	i;
	int		j;
	int		k;

	i = 0;
	j = size;
	k = ft_strlen(s1);
	while (i < size && s2[i])
	{
		s1[k + i] = s2[i];
		i++;
	}
	s1[k + i] = '\0';
	return (s1);
}
