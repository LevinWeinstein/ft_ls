/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_l_3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 02:52:33 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/03 03:19:25 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

size_t	longest_group(const t_contents *set)
{
	t_contents	*copy;
	size_t		longest;
	size_t		current;

	longest = 0;
	copy = (t_contents*)set;
	while (copy != NULL)
	{
		current = ft_strlen(copy->details->group);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}

size_t	get_digits(size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while (n != 0 && ++i)
		n /= 10;
	return (i);
}

size_t	link_digits(const t_contents *set)
{
	t_contents	*copy;
	size_t		longest;
	size_t		current;

	longest = 0;
	copy = (t_contents*)set;
	while (copy != NULL)
	{
		current = get_digits(copy->details->links);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}

size_t	byte_digits(const t_contents *set)
{
	t_contents	*copy;
	size_t		longest;
	size_t		current;

	longest = 0;
	copy = (t_contents*)set;
	while (copy != NULL)
	{
		current = get_digits(copy->details->bytes);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}

void	check_link(t_ls *home, t_contents check)
{
	char	linked_from[PATH_MAX + 1];
	char	linked_to[PATH_MAX + 1];

	if ((S_ISLNK(check.stats->st_mode)))
	{
		ft_bzero(linked_to, PATH_MAX + 1);
		ft_bzero(linked_from, PATH_MAX + 1);
		combine_path(linked_from, home->cur, check.name);
		readlink(linked_from, linked_to, PATH_MAX + 1);
		ft_putstr(" -> ");
		ft_putstr(linked_to);
	}
	ft_putchar('\n');
}
