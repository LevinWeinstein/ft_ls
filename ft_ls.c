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

void		ft_putstr_nl(const char *str)
{
	ft_putstr(str);
	ft_putchar('\n');
}

void		name_error(char *filename)
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

void	revtime_sort(t_contents **contents)
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
			if (i->stats->st_mtime < j->stats->st_mtime)
				swap_contents(i, j);
			else if (i->stats->st_mtime == j->stats->st_mtime
					&& ft_strcmp(i->name, j->name) > 0)
				swap_contents(i, j);
			j = j->next;
		}
		i = i->next;
	}
}

void	revsort_contents(t_contents **contents)
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
			if (ft_strcmp(i->name, j->name) < 0)
				swap_contents(i, j);
			j = j->next;
		}
		i = i->next;
	}
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

t_contents	*new_item(t_ls *ls, struct dirent *ent)
{
	t_contents	*output;
	struct stat	tmp;
	char		*tmp1;
	char		*tmp2;

	tmp1 = ft_strjoin(ls->cur, "/");
	output = (t_contents*)malloc(sizeof(t_contents));
	output->stats = (struct stat*)malloc(sizeof(struct stat));
	output->name = ft_strdup(ent->d_name);
	tmp2 = ft_strjoin(tmp1, ent->d_name);
	lstat(tmp2, &tmp);
	*output->stats = tmp;
	output->details = get_details(ls, *output);
	output->next = NULL;
	ft_strdel(&tmp1);
	ft_strdel(&tmp2);
	return (output);
}

void	print_items(t_contents *contents)
{
	if (contents == NULL)
		return ;
	ft_putprint(contents->name);
	ft_putchar('\n');
	print_items(contents->next);
}

void	print_visible(t_contents *contents)
{
	if (contents == NULL)
		return ;
	if (*contents->name != '.')
		ft_putstr_nl(contents->name);
	print_visible(contents->next);
}

void	print_named(t_contents *contents)
{
	if (contents == NULL)
		return ;
	if (ft_strcmp(contents->name, ".") != 0 &&
			ft_strcmp(contents->name, "..") != 0)
		ft_putstr_nl(contents->name);
	print_visible(contents->next);
}

t_ls	*noname_ls(void)
{
	t_ls *output;

	output = (t_ls*)malloc(sizeof(t_ls));
	output->items = NULL;
	output->dirs = NULL;
	output->next = NULL;
	output->namelist = NULL;
	output->total = 0;
	ft_memset(&output->stats, 0, sizeof(struct stat));
	return (output);
}

int		ls_add_namelist(t_ls_namelist **namelist, const char *str)
{
	t_ls_namelist *mover;
	t_ls_namelist *tmp;

	mover = (t_ls_namelist*)ft_memalloc(sizeof(t_ls_namelist));
	tmp = *namelist;
	ft_strncpy(mover->name, str, PATH_MAX + 1);
	if (*namelist == NULL)
		*namelist = mover;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = mover;
	}
	return (1);
}

void	combine_path(char *dst, char *left, char *right)
{
	int		i;
	int		j;

	if (right == NULL || (j = ft_strlen(right)) == 0)
		return ;
	if (left == NULL || (i = ft_strlen(left)) == 0)
		ft_strncpy(dst, right, PATH_MAX + 1);
	else
	{
		ft_strncpy(dst, left, i);
		dst[i++] = '/';
		ft_strncpy(dst + i, right, PATH_MAX + 1 - i);
	}
}

/*
** Blocks are added to home automatically in get_details
*/

int		a_filter(t_ls_flags a, char *name)
{
	if (ft_strlen(name) > 0 && name[0] == '.')
	{
		if (a.a == 0 && a.aa == 0)
			return (1);
		if (a.a > 0)
			return (0);
		if (a.aa > 0 && ft_strcmp(name, ".") != 0 && ft_strcmp(name, "..") != 0)
			return (0);
		if (a.aa > 0)
			return (1);
	}
	return (0);
}

t_ls	*single(t_ls_flags a, char *above, char *name)
{
	t_ls		*output;
	struct stat	item;
	char		tmp2[PATH_MAX + 1];
	int			d;

	output = noname_ls();
	combine_path(tmp2, above, name);
	output->cur = ft_strdup(tmp2);
	if ((output->open = opendir(output->cur)) == NULL)
		return (NULL);
	lstat(output->cur, &output->stats);
	while ((output->ent = readdir(output->open)) != NULL)
	{
		ft_memset(&item, 0, sizeof(struct stat));
		combine_path(tmp2, output->cur, output->ent->d_name);
		lstat(tmp2, &item);
		if (S_ISDIR(item.st_mode) && ft_strcmp(output->ent->d_name, ".") != 0
				&& ft_strcmp(output->ent->d_name, "..") != 0)
			ls_add_item(&output->dirs, new_item(output, output->ent));
		output->total += ((d = a_filter(a, output->ent->d_name)) != 0 ? \
			0 : item.st_blocks);
		ls_add_item(!d ? &output->items : NULL, new_item(output, output->ent));
	}
	closedir(output->open);
	return (output);
}

t_ls_namelist	*ls_readout(char *cur, const t_contents *items)
{
	t_ls_namelist	*namelist;
	t_contents		*l;
	char			tmp[PATH_MAX + 1];

	l = (t_contents*)items;
	namelist = NULL;
	while (l != NULL)
	{
		combine_path(tmp, cur, l->name);
		ls_add_namelist(&namelist, tmp);
		l = l->next;
	}
	return (namelist);
}

int	ft_ls_namerr(char *name)
{
	if (name == NULL || ft_strlen(name) < 1)
		ft_putstr_fd("ft_ls: fts_open: No such file or directory\n", 2);
	else
	{
		ft_putstr_fd("ft_ls: ", 2);
		perror(name);
	}
	return (errno);
}

void	do_nothing(void)
{
	return ;
}

t_contents	*not_dir(const char *str)
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

int		empty_flags(t_ls_flags *premade)
{
	premade->aa = 0;
	premade->rr = 0;
	premade->a = 0;
	premade->l = 0;
	premade->r = 0;
	premade->t = 0;
	return (UNUSEDRETURN);
}

int	bad_flag(char c)
{
	if (c == 'A' || c == 'R' || c == 'a' ||
			c == 'l' || c == 'r' || c == 't')
		return (42);
	ft_putstr_fd("ft_ls: illegal option -- ", 2);
	ft_putchar(c);
	ft_putstr_fd("\nusage: ft_ls [-ARalrt] [file...]\n", 2);
	exit(1);
}

int	ft_exit(const int code, const char *str)
{
	ft_putstr_nl(str);
	exit(code);
	return (UNUSEDRETURN);
}

/*
** The LS distributed on OS X [including lab computers] uses the
** <fts.h> functions. When this happens, ls closes with the errno
** ENOENT, even though fts_open is not a file or directory. This is
** most likely due to fts_open returning an FTS*
*/

int		empty_fts_error(char *argv)
{
	if (argv == NULL || ft_strlen(argv) == 0)
	{
		ft_putstr_fd("ft_ls: fts_open: No such file or directory\n", 2);
		return (1);
	}
	return (0);
}

int		get_flags(int argc, char **argv, t_ls_flags *flag)
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

/*
** ls shows ? when non-printable when inside a dir,
** but prints nothing in place of a non-printable
** while iterating through a dir.
*/

void	ft_dirprint(const char *str)
{
	int i;

	i = -1;
	if (str == NULL)
		return ;
	if (ft_strlen(str) >= 2 && str[0] == '/')
		++i;
	while(str[++i])
		if(ft_isprint(str[i]) == 1)
			ft_putchar(str[i]);
	ft_putstr(":\n");
}

t_ls_namelist *from_argv(int index, int argc, char **argv)
{
	t_ls_namelist *new;

	new = NULL;
	index--;
	while (++index < argc)
			ls_add_namelist(&new, argv[index]);
	return (new);
}

int only_one(t_ls_namelist *namelist)
{
	if (namelist == NULL)
		return (-1);
	if (namelist->next == NULL)
		return (1);
	return (0);
}

char	first_char(char *str)
{
	int i;

	i = ft_strlen(str - 1);
	if (i == -1 || str[i] == '/')
		return (-1);
	while(i > 0 && str[i - 1] != '/')
		i--;
	return (str[i]);
}

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

char	*solo_name(char *str)
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

int	do_level(t_ls_flags flags, t_ls_namelist *namelist, int top_and_one)
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

int		main(int argc, char **argv)
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
