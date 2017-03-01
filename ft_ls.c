/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:08:01 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/01 10:18:32 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

void	ft_putstr_nl(char *str)
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
	//output->name = ent->d_name;
	tmp2 = ft_strjoin(tmp1, ent->d_name);
	lstat(tmp2, &tmp);
	*output->stats = tmp;
	output->details = get_details(ls, *output); //replace with get_longform
	output->next = NULL;
	return (output);
}

void	print_items(t_contents *contents)
{
	if (contents == NULL)
		return ;
	ft_putstr_nl(contents->name);
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
	return (output);
}

t_ls	*single(char *above, char *name)
{
	t_ls *output;
	char	*tmp;
	struct	stat item;

	output = noname_ls();
	output->dirs = NULL;
	output->items = NULL;
	tmp = (above == NULL) ? NULL : ft_strjoin(above, "/");
	output->cur = ft_strjoin(tmp, name);
	if ((output->open = opendir(output->cur)) == NULL)
		return(NULL);
	while((output->ent = readdir(output->open)) != NULL)
	{
		ft_memset(&item, 0, sizeof(struct stat));
		stat(ft_strjoin(ft_strjoin(output->cur, "/"), output->ent->d_name), &item);
		if (S_ISDIR(item.st_mode) && ft_strcmp(output->ent->d_name, ".") != 0
				&& ft_strcmp(output->ent->d_name, "..") != 0)
			ls_add_item(&output->dirs, new_item(output, output->ent));
		ls_add_item(&output->items, new_item(output, output->ent));
	}
	if (tmp != NULL)
		free(tmp);
	return (output);
}


int		main(int argc, char **argv)
{
	char *str;
	DIR	 *open;
	struct dirent *cur;
	struct stat item;
	t_ls	*ls;

	ls = (t_ls*)malloc(sizeof(t_ls));
	ls->items = NULL;
	ls->dirs = NULL;
	ls->next = NULL;
	errno = 0;
	if (argc < 2)
		ls = single(NULL, ".");
	else if (argv[1][0] != '/' && argv[1][0] != '~')
		ls = single(NULL, ft_strdup(argv[1]));
	else
		ls = single(NULL, argv[1]);
	if (ls == NULL)
		perror("ls: ");
	else if (ls->dirs != NULL) //if (ls->dirs != NULL) or (ls->items != NULL) is critical in the
	{							//situation of an empty directory.
		sort_contents(&ls->dirs);
		ls->dirs->details = get_details(ls, *ls->dirs);
		//if (ls->dirs->details == NULL)
		//	ft_putstr("ANUS");
		//print_named(ls->dirs);
		print_long(ls, ls->dirs, ls->dirs);
	}
	return (0);
}
