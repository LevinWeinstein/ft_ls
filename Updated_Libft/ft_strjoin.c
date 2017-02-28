/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 01:20:22 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/27 01:48:32 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t		len;
	char		*output;
	size_t		i;
	char		c1;
	char		c2;

	if (s1 == NULL && s2 == NULL)
		return (NULL);
	if (s1 == NULL)
		return ((char *)s2);
	if (s2 == NULL)
		return ((char *)s1);
	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	if ((output = ft_strnew(len)) == NULL)
		return (NULL);
	i = 0;
	while ((c1 = *s1++) != '\0')
		output[i++] = c1;
	while ((c2 = *s2++) != '\0')
		output[i++] = c2;
	output[i] = '\0';
	return (output);
}
