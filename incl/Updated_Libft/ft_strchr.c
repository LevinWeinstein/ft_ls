/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 08:46:13 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/25 09:13:53 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char check;

	check = (char)c;
	while (*s != '\0' && *s != check)
		s++;
	if (*s == check)
		return ((char *)s);
	return (NULL);
}
