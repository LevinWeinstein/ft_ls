/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 00:18:43 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/26 01:02:39 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char t1;
	unsigned char t2;

	t1 = '\0';
	t2 = '\0';
	while (n > 0)
	{
		t1 = (unsigned char)*s1++;
		t2 = (unsigned char)*s2++;
		if (t1 == '\0' || t1 != t2)
			return (t1 - t2);
		n--;
	}
	return (t1 - t2);
}
