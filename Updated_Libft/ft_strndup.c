/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/29 23:39:34 by lweinste          #+#    #+#             */
/*   Updated: 2017/01/20 01:10:32 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t n)
{
	size_t	i;
	char	*output;

	i = 0;
	output = (char *)malloc((n + 1) * sizeof(char));
	if (!output)
		return (NULL);
	while (s1[i] && i < n)
	{
		output[i] = s1[i];
		i++;
	}
	while (i <= n)
		output[i++] = '\0';
	return (output);
}
