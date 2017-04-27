/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_basics_six.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:06:24 by lweinste          #+#    #+#             */
/*   Updated: 2017/04/26 14:13:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>

void			ft_dirprint(const char *str)
{
	int i;

	i = -1;
	if (str == NULL)
		return ;
	if (ft_strlen(str) >= 2 && str[0] == '/')
		++i;
	while (str[++i])
		if (ft_isprint(str[i]) == 1)
			ft_putchar(str[i]);
	ft_putstr(":\n");
}

t_ls_namelist	*from_argv(int index, int argc, char **argv)
{
	t_ls_namelist *new;

	new = NULL;
	index--;
	while (++index < argc)
		ls_add_namelist(&new, argv[index]);
	return (new);
}

int				only_one(t_ls_namelist *namelist)
{
	if (namelist == NULL)
		return (-1);
	if (namelist->next == NULL)
		return (1);
	return (0);
}

char			first_char(char *str)
{
	int i;

	i = ft_strlen(str - 1);
	if (i == -1 || str[i] == '/')
		return (-1);
	while (i > 0 && str[i - 1] != '/')
		i--;
	return (str[i]);
}
