/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 18:08:01 by lweinste          #+#    #+#             */
/*   Updated: 2017/02/28 22:38:30 by lweinste         ###   ########.fr       */
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
	t_longform		details;

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

t_contents *new_item(struct dirent *ent)
{
	t_contents *output;
	struct stat	tmp;

	output = (t_contents*)malloc(sizeof(t_contents));
	output->stats = (struct stat*)malloc(sizeof(struct stat));
	output->name = ft_strdup(ent->d_name);
	lstat(ent->d_name, &tmp);
	*output->stats = tmp;
	//output->details = NULL; //replace with get_longform
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
	if (argc < 2)
		ls->cur = ft_strdup(".");
	else
		ls->cur = ft_strdup(argv[1]);
	if ((ls->open = opendir(ls->cur)) == NULL)
		return (-1);
	while ((ls->ent = readdir(ls->open)) != NULL)
	{
		lstat(ls->ent->d_name, &item);
		if (S_ISDIR(item.st_mode) && ft_strcmp(ls->ent->d_name, ".") != 0
				&& ft_strcmp(ls->ent->d_name, "..") != 0)
			ls_add_item(&ls->dirs, new_item(ls->ent)); 
		ls_add_item(&ls->items, new_item(ls->ent));
		//print_items(ls->items);
		//ft_putstr_nl(cur->d_name);
	}
	sort_contents(&ls->dirs);
	print_items(ls->dirs);
	return (0);
}
