/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 09:03:01 by exam              #+#    #+#             */
/*   Updated: 2016/12/15 04:58:54 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		g_values[] = {'0', '1', '2', '3', '4', '5',
	'6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static char		*str_zero(void)
{
	char *output;

	output = (char *)malloc(2 * sizeof(char));
	output[0] = '0';
	output[1] = '\0';
	return (output);
}

static uintmax_t		safe_mod(uintmax_t n, int base)
{
	uintmax_t m;

	m = n % base;
	return (m);
}

static int		get_digits(uintmax_t value, int base)
{
	int i;

	i = 0;
	while (value != 0)
	{
		value /= base;
		i++;
	}
	return (i);
}

char			*ft_utoa_base_lower(uintmax_t value, int base)
{
	int		digits;
	char	*output;
	uintmax_t		safemod;

	if (base < 2 || base > 16)
		return ((char *)0);
	if (value == 0)
		return ((output = str_zero()));
	digits = get_digits(value, base);
	output = (char *)malloc((digits + 1) * sizeof(char));
	output[digits] = '\0';
	while (value != 0)
	{
		safemod = safe_mod(value, base);
		output[--digits] = g_values[safemod];
		value /= base;
	}
	return (output);
}
