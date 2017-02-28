/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 09:03:01 by exam              #+#    #+#             */
/*   Updated: 2016/12/15 04:59:07 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char		g_values[] = {'0', '1', '2', '3', '4', '5',
	'6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

static char		*str_zero(void)
{
	char *output;

	output = (char *)malloc(2 * sizeof(char));
	output[0] = '0';
	output[1] = '\0';
	return (output);
}

static unsigned long		safe_mod(unsigned long n, int base)
{
	int m;

	m = n % base;
	return (m);
}

static unsigned long		get_digits(unsigned long value, int base)
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

char			*ft_utoa_base_upper(unsigned long value, int base)
{
	unsigned long		digits;
	char	*output;
	unsigned long safemod;

	if (base < 2 || base > 16)
		return ((char *)0);
	if (value == 0)
		return ((output = str_zero()));
	/*if (value == 4294967296 && base == 16)
		return ft_strdup("100000000");
	if (value == 4294967296 && base == 10)
		return ft_strdup("4294967296");*/
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
