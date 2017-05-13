/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:08:01 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/03 09:57:56 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

/*
** ls shows a question mark  when non-printable 
** when inside a dir,
** but prints nothing in place of a non-printable
** while iterating through a dir.
*/

t_ls_namelist	*delete_element(t_ls_namelist *namelist, int position)
{
	t_ls_namelist	*tmp;
	t_ls_namelist	*kill;
	int				i;

	i = 1;
	tmp = namelist;
	if (namelist == NULL)
		return (NULL);
	if (position == 0)
	{
		namelist = tmp->next;
		free(tmp);
		tmp = NULL;
		return (namelist);
	}
	while (i++ < position)
		tmp = tmp->next;
	kill = tmp->next;
	tmp->next = kill->next;
	free(kill);
	kill = NULL;
	return (namelist);
}

char			*solo_name(char *str)
{
	int i;

	i = ft_strlen(str);
	if (str == NULL || i < 1)
		return (NULL);
	if (str[i - 1] == '/')
		return (NULL);
	while (--i >= 0)
	{
		if (str[i] == '/')
			return (str + i + 1);
	}
	return (str);
}

t_ls_namelist	*clean_dots(t_ls_namelist *namelist, t_ls_flags flags)
{
	char *tmp;

	if (namelist == NULL)
		return (NULL);
	if (flags.a || flags.aa)
		return (namelist);
	tmp = solo_name(namelist->name);
	if (tmp != NULL && tmp[0] == '.' && (flags.a <= 0 && flags.aa <= 0))
	{
		namelist = delete_element(namelist, 0);
		namelist = clean_dots(namelist, flags);
	}
	else
		namelist->next = clean_dots(namelist->next, flags);
	return (namelist);
}

int				do_level(t_ls_flags flags, \
		t_ls_namelist *namelist, int top_and_one)
{
	t_ls_namelist *next;

	if (namelist == NULL)
		return (1);
	while (namelist != NULL)
	{
		ft_putchar('\n');
		if (top_and_one <= 0)
			ft_dirprint(namelist->name);
		next = clean_dots(inner(flags, namelist->name), flags);
		do_level(flags, next, 0);
		namelist = namelist->next;
	}
	return (1);
}

int				main(int argc, char **argv)
{
	int				i;
	struct stat		stats;
	char			tmp[PATH_MAX + 1];
	t_ls_namelist	*nlst[2];
	t_ls_flags		flags;

	nlst[0] = NULL;
	empty_flags(&flags);
	ft_bzero(&stats, sizeof(struct stat));
	ft_bzero(tmp, PATH_MAX + 1);
	ft_strncpy(tmp, ".\0", MAXNAMLEN + 1);
	if (((errno = 0) == 0 && argc == 1) ||
		(argc > 1 && (i = get_flags(argc, argv, &flags)) == ONLYFLAGS))
		ls_add_namelist(&nlst[0], tmp);
	else if (argc > 1)
		nlst[0] = from_argv(i, argc, argv);
	flags.one = only_one(nlst[0]);
	while (nlst[0] != NULL)
	{
		ft_dirprint((!flags.one) ? (nlst[0])->name : NULL);
		nlst[1] = clean_dots(inner(flags, (nlst[0])->name), flags);
		nlst[0] = (nlst[0])->next;
		(nlst[1] != NULL && flags.rr) ? do_level(flags, nlst[1], 0) : 1;
	}
	return (0);
}
