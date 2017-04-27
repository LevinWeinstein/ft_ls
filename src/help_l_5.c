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

void		grab_name(t_ls *home, t_contents *contents)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (home == NULL || home->cur == NULL ||
			contents == NULL || contents->name == NULL)
		return ;
	j = ft_strlen(contents->name) - 1;
	i = j;
	while (i > 0 && contents->name[i] != '\\')
		i--;
	j -= i - 1;
	str = ft_strndup(contents->name + i, j);
	ft_putprint(str);
	ft_strdel(&str);
}

void		ok_putnbr(intmax_t n)
{
	int	negative;

	if ((negative = (n < 0 ? -1 : 1)) == -1)
		ft_putchar('-');
	if (n >= 10 || n <= -10)
		ok_putnbr((n / 10) * negative);
	ft_putchar('0' + ((n % 10) * negative));
}

void		print_total(long long blocks)
{
	ft_putstr("total ");
	ok_putnbr(blocks);
	ft_putchar('\n');
}

t_longform	*get_details_single(t_contents contents)
{
	t_longform	*output;
	struct stat	test;

	if (lstat(contents.name, &test) == -1)
		return (NULL);
	output = (t_longform*)malloc(sizeof(t_longform));
	output->mode = get_mode(contents);
	output->links = count_links(contents);
	output->rights = get_rights(contents);
	output->user = get_user(contents);
	output->group = get_group(contents);
	output->bytes = count_bytes(contents);
	output->time = time_string(contents.stats->st_mtime);
	return (output);
}
