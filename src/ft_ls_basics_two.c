/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_basics_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:10:13 by lweinste          #+#    #+#             */
/*   Updated: 2017/04/26 06:13:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>

void	time_sort(t_contents **contents)
{
	t_contents *i;
	t_contents *j;

	if (*contents == NULL || (*contents)->next == NULL)
		return ;
	i = *contents;
	while (i != NULL)
	{
		j = i->next;
		while (j != NULL)
		{
			if (i->stats->st_mtimespec.tv_sec <
				j->stats->st_mtimespec.tv_sec)
				swap_contents(i, j);
			else if (i->stats->st_mtimespec.tv_sec ==
				j->stats->st_mtimespec.tv_sec &&
				ft_strcmp(i->name, j->name) < 0)
				swap_contents(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

void	reverse_contents(t_contents **contents)
{
	t_contents *a;
	t_contents *b;
	t_contents *c;

	if (contents == NULL || (*contents) == NULL || (*contents)->next == NULL)
		return ;
	a = *contents;
	b = *contents;
	c = *contents;
	a = a->next->next;
	b = b->next;
	c->next = NULL;
	b->next = c;
	while (a != NULL)
	{
		c = b;
		b = a;
		a = a->next;
		b->next = c;
	}
	*contents = b;
}

void	ls_add_item(t_contents **ls, t_contents *add)
{
	if (ls == NULL || add == NULL)
		return ;
	if (*ls == NULL)
		*ls = add;
	else
		ls_add_item(&(*ls)->next, add);
}
