/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 21:14:18 by lweinste          #+#    #+#             */
/*   Updated: 2016/09/27 23:31:08 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	wordcount(const char *s, char c)
{
	int		toggle;
	size_t	count;
	char	*cpy;

	toggle = 0;
	count = 0;
	cpy = (char *)s;
	while (*cpy != '\0')
	{
		if (*cpy != c && !toggle)
		{
			toggle = 1;
			count++;
		}
		if (*cpy == c && toggle)
			toggle = 0;
		cpy++;
	}
	return (count);
}

static	size_t	delim_strlen(const char *s, char c)
{
	size_t i;

	i = 0;
	while (s[i] != '\0' && s[i] != c)
		i++;
	return (i);
}

static char		*nextword(const char *s, char c, size_t *n)
{
	size_t	i;
	size_t	count;
	char	*output;
	int		g;

	i = *n;
	g = 0;
	while (s[i] == c)
		i++;
	count = delim_strlen((s + i), c);
	output = ft_strnew(count);
	while (count--)
		output[g++] = s[i++];
	output[g] = '\0';
	*n = i;
	return (output);
}

char			**ft_strsplit(char const *s, char c)
{
	char	*cpy;
	size_t	n;
	int		i;
	int		count;
	char	**output;

	i = 0;
	n = 0;
	if (!s || !c)
		return (NULL);
	count = wordcount(s, c);
	cpy = (char *)s;
	if ((output = (char **)malloc(sizeof(char*) * (count + 1))) == NULL)
		return (NULL);
	while (i < count)
		output[i++] = nextword(cpy, c, &n);
	output[i] = 0;
	return (output);
}
