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
	ft_putstr("ls: " );
	perror(str);
}

t_contents *new_link(char *str)
{
	t_contents *output;
	output = (t_contents*)malloc(sizeof(t_contents));
	output->name = ft_strjoin(str, "/");
	errno = 0;
	if (lstat(output->name, output->stats) == -1 && errno != ENOTDIR)
	{
		name_error(output->name);
		free(output->name);
		free(output);
		output = NULL;
		return (NULL);
	}
	output->next = NULL;
	return (output);
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

void	reverse_contents(t_contents **contents)
{
	t_contents *a;
	t_contents *b;
	t_contents *c;

	if (contents == NULL ||(*contents) == NULL || (*contents)->next == NULL)
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
	while(i != NULL)
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

void	ls_add_back(t_ls **ls, t_ls *add)
{
	if (ls == NULL || add == NULL)
		return ;
	if (*ls == NULL)
		*ls = add;
	else
		ls_add_back(&(*ls)->next, add);
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

t_contents *new_item(t_ls *ls, struct dirent *ent)
{
	t_contents *output;
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
	output->details = get_details(ls, *output); //replace with get_longform
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

		mover = (t_ls_namelist*)malloc(sizeof(t_ls_namelist));
		ft_strncpy(mover->name, str, PATH_MAX + 1);
		mover->next = *namelist;
		*namelist = mover;
		return (1);
}

void	combine_path(char *dst, char *left, char *right)
{
	int		i;
	int		j;

	if (right == NULL || (j = ft_strlen(right))== 0)
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
	t_ls *output;
	struct	stat item;
	char	tmp2[PATH_MAX + 1];
	int		d;

	output = noname_ls();
	combine_path(tmp2, above, name);
	output->cur = ft_strdup(tmp2);
	if ((output->open = opendir(output->cur)) == NULL)
		return(NULL);	
	lstat(output->cur, &output->stats);
	while((output->ent = readdir(output->open)) != NULL)
	{
		ft_memset(&item, 0, sizeof(struct stat));
		combine_path(tmp2, output->cur, output->ent->d_name);
		lstat(tmp2, &item);
		if (S_ISDIR(item.st_mode) && ft_strcmp(output->ent->d_name, ".") != 0
				&& ft_strcmp(output->ent->d_name, "..") != 0)
			ls_add_item(&output->dirs, new_item(output, output->ent));
			//output->dcnt = ls_add_namelist(&output->namelist, tmp2);
		output->total += ((d = a_filter(a, output->ent->d_name)) != 0 ? 0 : item.st_blocks);
		ls_add_item( !d ? &output->items : NULL, new_item(output, output->ent));
	}
	closedir(output->open);
	return (output);
}

t_ls_namelist *ls_readout(char *cur, const t_contents *items)
{
	t_ls_namelist *namelist;
	t_contents *l;
	char	tmp[PATH_MAX + 1];

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
	ft_putstr_fd("ft_ls: ", 2);
	perror(name);
	return (errno);
}
void	do_nothing(void)
{
	return ;
}



t_ls_namelist *inner(t_ls_flags flags, char *dirname)
{
	t_ls	*ls;

	errno = 0;
	ls = single(flags, NULL, dirname);
	if (ls == NULL || flags.l == -42)
		ft_ls_namerr(dirname);
	else if (ls != NULL && ls->items != NULL)
	{
		if(flags.l && ls->total > 0)
			print_total(ls->total);	
		flags.t > 0 ? time_sort(&ls->items) : sort_contents(&ls->items);
		flags.r > 0 ? reverse_contents(&ls->items) : do_nothing();
		if (ls->dirs != NULL)
		{
			flags.t > 0 ? time_sort(&ls->dirs) : sort_contents(&ls->dirs);
			flags.r > 0 ? time_sort(&ls->dirs) : do_nothing();
		}
		ls->items->details = get_details(ls, *ls->items);
		if (flags.l && ls != NULL)
			print_long(ls, ls->items, ls->items);
		else
			print_items(ls->items);
	}
	return (ls != NULL ? ls_readout(dirname, ls->dirs): NULL);
}

int		empty_flags(t_ls_flags *premade)
{
	premade->aa = 0;
	premade->rr = 0;

	premade->a = 0;
	premade->l = 0;
	premade->r = 0;
	premade->t = 0;
	return(UNUSEDRETURN);
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
	return(UNUSEDRETURN);
}

/*
** The LS distributed on OS X [including lab computers] uses the
** <fts.h> functions. When this happens, ls closes with the errno
** ENOENT, even though fts_open is not a file or directory. This is
** most likely due to fts_open returns an FTS*
*/

int	empty_fts_error(char *argv)
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
	while(++i < argc && ft_strlen(argv[i]) != 0 && argv[i][0] == '-')
	{
		j = 0;
		which++;
		len = ft_strlen(argv[i]);
		while(++j < len && bad_flag(argv[i][j]))
		{
			flag->aa = argv[i][j] == 'A' ? which : flag->aa;
			flag->rr = argv[i][j] == 'R' ? which : flag->rr;
			flag->a = argv[i][j] == 'a' ? which : flag->a;
			flag->l = argv[i][j] == 'l' ? which :  flag->l;
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

int		ls_namelist_recurse(t_ls_flags flags, t_ls_namelist *name)
{
	//int i;
	t_ls_namelist *tmp;
	
	if (name == NULL)
		return -1;
	printf("%s:\n", name->name);
	while (name != NULL && ft_strlen(name->name) > 0)
	{
		tmp = inner(flags, name->name);
		if (flags.rr)
			ls_namelist_recurse(flags, (inner(flags, name->name)));
		name = name->next;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	int	i;
	struct stat stats;
	t_ls_namelist *namelist;
	t_ls_flags flags;
	char	tmp[PATH_MAX + 1];

	namelist = NULL;	
	empty_flags(&flags);
	ft_bzero(&stats, sizeof(struct stat));
	ft_bzero(tmp, PATH_MAX + 1);
	ft_strncpy(tmp, ".\0", MAXNAMLEN + 1);
	//puts(tmp);
	if (argc == 1)
		ls_add_namelist(&namelist, tmp);
	else
		i = get_flags(argc, argv, &flags);
	errno = 0;
	if (argc > 1 && i == ONLYFLAGS)
		ls_add_namelist(&namelist, tmp);
	else if (argc > 1)
		namelist = from_argv(i, argc, argv);
	if (namelist != NULL)
		ls_namelist_recurse(flags, namelist);
	return (0);
}

