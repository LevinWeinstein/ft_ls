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

void	print_long(t_ls *home, t_contents *safe, t_contents *set)
{
	size_t	i;

	i = 0;
	if (set == NULL || set->details == NULL)
		return ;
	ft_charstr(set->details->mode, set->details->rights);
	while (i++ <= 1 + (link_digits(safe) - get_digits(set->details->links)))
		ft_putchar(' ');
	ft_putnbr((i = 0) < 2 ? (int)set->details->links : 0);
	while (i++ <= longest_user(safe) - ft_strlen(set->details->user))
		ft_putchar(' ');
	ft_putstr((i = 0) < 2 ? set->details->user : "?\0");
	while (i++ <= 1 + longest_group(safe) - ft_strlen(set->details->group))
		ft_putchar(' ');
	ft_putstr((i = 0) < 1 ? set->details->group : "?\0");
	while (i++ <= 1 + byte_digits(safe) - get_digits(set->details->bytes))
		ft_putchar(' ');
	ft_numspace(set->details->bytes);
	ft_putspace(set->details->time);
	grab_name(home, set);
	check_link(home, *set);
	print_long(home, safe, set->next);
}

void	print_long_single(t_contents *safe, t_contents *set)
{
	size_t	i;

	i = 0;
	if (set == NULL || set->details == NULL)
		return ;
	ft_charstr(set->details->mode, set->details->rights);
	while (i++ <= 1 + (link_digits(safe) - get_digits(set->details->links)))
		ft_putchar(' ');
	ft_putnbr((i = 0) < 2 ? (int)set->details->links : 0);
	while (i++ <= longest_user(safe) - ft_strlen(set->details->user))
		ft_putchar(' ');
	ft_putstr((i = 0) < 2 ? set->details->user : "?\0");
	while (i++ <= 1 + longest_group(safe) - ft_strlen(set->details->group))
		ft_putchar(' ');
	ft_putstr((i = 0) < 1 ? set->details->group : "?\0");
	while (i++ <= 1 + byte_digits(safe) - get_digits(set->details->bytes))
		ft_putchar(' ');
	ft_numspace(set->details->bytes);
	ft_putspace(set->details->time);
	ft_putstr(set->name);
	check_link_single(*set);
}
