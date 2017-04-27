/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 02:52:33 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/03 03:19:25 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

void	check_link_single(t_contents check)
{
	char	linked_from[PATH_MAX + 1];
	char	linked_to[PATH_MAX + 1];

	if ((S_ISLNK(check.stats->st_mode)))
	{
		ft_bzero(linked_to, PATH_MAX + 1);
		ft_bzero(linked_from, PATH_MAX + 1);
		if (check.name[0] != '/')
			combine_path(linked_from, ".", check.name);
		else
			ft_strcpy(linked_from, check.name);
		readlink(linked_from, linked_to, PATH_MAX + 1);
		ft_putstr(" -> ");
		ft_putstr(linked_to);
	}
	ft_putchar('\n');
}

void	ft_putspace(char *str)
{
	ft_putstr(str);
	ft_putchar(' ');
}

void	ft_charstr(char c, char *str)
{
	ft_putchar(c);
	ft_putstr(str);
}

void	ft_numspace(int n)
{
	ft_putnbr(n);
	ft_putchar(' ');
}

void	ft_putprint(const char *str)
{
	int		i;
	char	c;

	i = -1;
	while ((c = str[++i]) != '\0')
		ft_putchar(ft_isprint(c) > 0 ? c : '?');
}
