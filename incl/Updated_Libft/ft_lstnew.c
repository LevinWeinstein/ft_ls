/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/28 18:03:18 by lweinste          #+#    #+#             */
/*   Updated: 2017/01/20 01:40:38 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list	*output;

	if (!(output = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	output->next = NULL;
	output->content_size = ((content == NULL) ? 0 : content_size);
	if (content_size == 0)
		return (!(output->content = NULL) ? output : output);
	output->content = ft_memalloc(content_size);
	ft_memmove(output->content, content, content_size);
	return (output);
}
