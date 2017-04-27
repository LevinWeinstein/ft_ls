/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_basics_five.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:06:24 by lweinste          #+#    #+#             */
/*   Updated: 2017/04/26 14:13:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>

t_contents		*not_dir(const char *str)
{
	t_contents	*new;
	struct stat	*stats;

	new = (t_contents*)ft_memalloc(sizeof(t_contents));
	new->next = NULL;
	new->name = ft_strdup(str);
	stats = (struct stat*)ft_memalloc(sizeof(struct stat));
	lstat(str, stats);
	new->stats = stats;
	new->details = get_details_single(*new);
	return (new);
}

t_ls_namelist	*inner(t_ls_flags flags, char *dirname)
{
	t_ls	*ls;

	errno = 0;
	ls = single(flags, NULL, dirname);
	if ((ls == NULL || flags.l == -42) && errno != ENOTDIR)
		ft_ls_namerr(dirname);
	else if ((ls == NULL || flags.l == -42))
		flags.l > 0 ? PLS(not_dir(dirname)) : ft_putendl(dirname);
	if (ls != NULL && ls->items != NULL && flags.l != -42)
	{
		if (flags.l && ls->total > 0)
			print_total(ls->total);
		flags.t > 0 ? time_sort(&ls->items) : sort_contents(&ls->items);
		flags.r > 0 ? reverse_contents(&ls->items) : do_nothing();
		if (ls->dirs != NULL)
		{
			flags.t > 0 ? time_sort(&ls->dirs) : sort_contents(&ls->dirs);
			flags.r > 0 ? time_sort(&ls->dirs) : do_nothing();
		}
		ls->items->details = get_details(ls, *ls->items);
		(flags.l && ls != NULL) ? PL(ls, ls->items) : print_items(ls->items);
	}
	return (ls != NULL ? ls_readout(dirname, ls->dirs) : NULL);
}

int				empty_flags(t_ls_flags *premade)
{
	premade->aa = 0;
	premade->rr = 0;
	premade->a = 0;
	premade->l = 0;
	premade->r = 0;
	premade->t = 0;
	return (UNUSEDRETURN);
}

int				bad_flag(char c)
{
	if (c == 'A' || c == 'R' || c == 'a' ||
			c == 'l' || c == 'r' || c == 't')
		return (42);
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar(c);
	ft_putstr_fd("\nusage: ft_ls [-ARalrt] [file...]\n", 2);
	exit(1);
}

int				get_flags(int argc, char **argv, t_ls_flags *flag)
{
	int	i;
	int	j;
	int which;
	int	len;

	i = 0;
	which = 0;
	empty_flags(flag);
	while (++i < argc && ft_strlen(argv[i]) != 0 && argv[i][0] == '-')
	{
		j = 0;
		which++;
		len = ft_strlen(argv[i]);
		while (++j < len && bad_flag(argv[i][j]))
		{
			flag->aa = argv[i][j] == 'A' ? which : flag->aa;
			flag->rr = argv[i][j] == 'R' ? which : flag->rr;
			flag->a = argv[i][j] == 'a' ? which : flag->a;
			flag->l = argv[i][j] == 'l' ? which : flag->l;
			flag->r = argv[i][j] == 'r' ? which : flag->r;
			flag->t = argv[i][j] == 't' ? which : flag->t;
		}
	}
	return (i == argc ? ONLYFLAGS : i);
}
