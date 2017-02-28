/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/27 02:28:15 by lweinste          #+#    #+#             */
/*   Updated: 2016/10/07 15:56:19 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		only_spaces(const char *s)
{
	int		i;

	i = 0;
	while (s[i] != '\0' && (s[i] == '\t' || s[i] == ' ' || s[i] == '\n'))
		i++;
	if (i < (int)ft_strlen(s))
		return (0);
	return (1);
}

char			*ft_strtrim(char const *s)
{
	char			*output;
	int				i;
	int				j;
	size_t			ltmp;

	if (s == NULL)
		return (NULL);
	i = -1;
	j = 0;
	ltmp = ft_strlen(s);
	while (s[ltmp - 1] == ' ' || s[ltmp - 1] == '\t' || s[ltmp - 1] == '\n')
		ltmp--;
	while (s[++i] == ' ' || s[i] == '\t' || s[i] == '\n')
		;
	if (only_spaces(s) || ltmp == 0)
		return (ft_strdup(""));
	if ((output = ft_strnew(ltmp - i)) == NULL)
		return (NULL);
	while (i++ < (int)ltmp)
		output[j++] = s[i - 1];
	output[j] = '\0';
	return (output);
}
