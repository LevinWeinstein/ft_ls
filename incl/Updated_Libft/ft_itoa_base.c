/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 09:03:01 by exam              #+#    #+#             */
/*   Updated: 2016/12/15 01:02:18 by lweinste         ###   ########.fr       */
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

static long		abs_val(long n)
{
	return (n >= 0 ? n : (n * -1));
}

static long		safe_abs_mod(long n, int base)
{
	int m;

	m = n % base;
	return (abs_val(m));
}

static long		get_digits(long value, int base)
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

char			*ft_itoa_base(long value, int base)
{
	int		negative;
	int		digits;
	char	*output;
	int		safemod;

	if (base < 2 || base > 16)
		return ((char *)0);
	if (value == 0)
		return ((output = str_zero()));
	negative = ((value < 0 && base == 10) ? 1 : 0);
	digits = get_digits(value, base);
	digits += negative;
	output = (char *)malloc((digits + 1) * sizeof(char));
	output[digits] = '\0';
	if (negative)
		output[0] = '-';
	while (value != 0)
	{
		safemod = safe_abs_mod(value, base);
		output[--digits] = g_values[safemod];
		value /= base;
	}
	return (output);
}
