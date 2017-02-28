/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memalloc.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 01:10:22 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/26 01:26:41 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memalloc(size_t size)
{
	char	*output;

	output = (char *)malloc(size * sizeof(output));
	if (output == NULL)
		return (NULL);
	ft_bzero(output, size);
	return ((void*)output);
}
