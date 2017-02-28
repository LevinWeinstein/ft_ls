/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:08:01 by lweinste          #+#    #+#             */
/*   Updated: 2017/02/07 18:31:28 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

void	ft_putstr_nl(char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

int		main(int argc, char **argv)
{
	char *str;
	DIR	 *open;
	struct dirent *cur;
	struct stat item;

	if (argc < 2)
		str = ft_strdup(".");
	else
		str = ft_strdup(argv[1]);
	if ((open = opendir(str)) == NULL)
		return (-1);
	while ((cur = readdir(open)) != NULL)
	{
		lstat(cur->d_name, &item);
		if (S_ISDIR(item.st_mode))
			ft_putstr("Directory :");
		else
			ft_putstr("Not Directory:");
		ft_putstr_nl(cur->d_name);
	}
	return (0);
}
