/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 22:13:48 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/26 00:18:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strcmp(const char *s1, const char *s2)
{
	unsigned char t1;
	unsigned char t2;

	t1 = (unsigned char)*s1;
	t2 = (unsigned char)*s2;
	while (t1 == t2)
	{
		t1 = (unsigned char)*s1++;
		t2 = (unsigned char)*s2++;
		if (t1 == '\0')
			return (t1 - t2);
	}
	return (t1 - t2);
}
