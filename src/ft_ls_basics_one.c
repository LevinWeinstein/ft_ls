/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_basics_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:06:24 by lweinste          #+#    #+#             */
/*   Updated: 2017/04/26 14:13:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>

void	ft_putstr_nl(const char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

void	name_error(char *filename)
{
	char	*str;
	size_t	len;

	len = ft_strlen(filename);
	str = ft_strndup(filename, len - 1);
	ft_putstr("ls: ");
	perror(str);
}

void	print_contents(t_ls *cur, t_contents *contents)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (cur == NULL || contents == NULL || contents->name == NULL)
		return ;
	i = ft_strlen(cur->cur);
	j = ft_strlen(contents->name) - i - 1;
	str = ft_strndup(contents->name + i, j);
	ft_putendl(str);
	ft_strdel(&str);
	print_contents(cur, contents->next);
}

void	swap_contents(t_contents *one, t_contents *two)
{
	char			*name;
	struct stat		*stats;
	t_longform		*details;

	details = one->details;
	name = one->name;
	stats = one->stats;
	one->name = two->name;
	one->stats = two->stats;
	one->details = two->details;
	two->name = name;
	two->stats = stats;
	two->details = details;
}

void	sort_contents(t_contents **contents)
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
			if (ft_strcmp(i->name, j->name) > 0)
				swap_contents(i, j);
			j = j->next;
		}
		i = i->next;
	}
}
