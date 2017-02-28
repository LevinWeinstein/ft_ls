/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/25 20:47:14 by lweinste          #+#    #+#             */
/*   Updated: 2016/10/04 16:34:51 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *s)
{
	char			*str;
	unsigned long	output;
	unsigned int	nextdigit;
	int				negative;

	str = (char *)s;
	output = 0;
	negative = 1;
	while (*str == ' ' || *str == '\t' || *str == '\v' ||
			*str == '\f' || *str == '\n' || *str == '\r')
		str++;
	if (*str == '+')
		str++;
	else if (*str == '-')
	{
		negative = -1;
		str++;
	}
	while (*str != '\0' && *str >= '0' && *str <= '9')
	{
		nextdigit = (unsigned int)(*str++ - '0');
		output = ((output * 10) + nextdigit);
	}
	return ((int)output * negative);
}
