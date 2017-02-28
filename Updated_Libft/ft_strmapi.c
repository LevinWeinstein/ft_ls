/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 23:02:38 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/26 23:39:51 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*output;
	unsigned int	index;

	index = 0;
	if (!s || !f)
		return (NULL);
	if ((output = (char *)malloc((ft_strlen(s) + 1) * sizeof(*output))) == NULL)
		return (NULL);
	while (s[index])
	{
		output[index] = (*f)(index, s[index]);
		index++;
	}
	output[index] = '\0';
	return (output);
}
