/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 22:23:08 by lweinste          #+#    #+#             */
/*   Updated: 2016/10/07 15:55:43 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int			ft_abs(int n)
{
	if (n < 0)
		n *= -1;
	return (n);
}

static	char		*handle_zeros(void)
{
	char	*output;

	output = (char *)malloc(2 * sizeof(char));
	*output = '0';
	output[1] = '\0';
	return (output);
}

static int			digits(int n)
{
	int dig;

	dig = 0;
	while (n != 0)
	{
		dig++;
		n /= 10;
	}
	return (dig);
}

char				*ft_itoa(int n)
{
	int		dig;
	int		neg;
	char	*output;
	char	*tmp;

	neg = 0;
	if (n == 0)
		return (handle_zeros());
	if (n <= -1)
		neg = 1;
	dig = digits(n);
	output = ft_strnew((size_t)(dig + neg));
	if (output == NULL)
		return (NULL);
	tmp = (char *)(output + dig + neg);
	*tmp-- = '\0';
	if (neg)
		*output = '-';
	while (n != 0 && n != -0)
	{
		*tmp-- = (ft_abs(n % 10) + '0');
		n /= 10;
	}
	return (output);
}
