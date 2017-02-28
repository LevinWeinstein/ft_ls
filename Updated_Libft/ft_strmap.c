/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/26 18:46:09 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/26 23:39:06 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	char	*output;
	int		i;

	i = 0;
	if (!s || !f)
		return (NULL);
	if ((output = (char *)malloc((ft_strlen(s) + 1) * sizeof(*output))) == NULL)
		return (NULL);
	while (s[i])
	{
		output[i] = f(s[i]);
		i++;
	}
	output[i] = '\0';
	return (output);
}
