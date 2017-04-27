/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_basics_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:06:24 by lweinste          #+#    #+#             */
/*   Updated: 2017/04/26 14:13:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>

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

void		print_items(t_contents *contents)
{
	if (contents == NULL)
		return ;
	ft_putprint(contents->name);
	ft_putchar('\n');
	print_items(contents->next);
}

t_ls		*noname_ls(void)
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

int			ls_add_namelist(t_ls_namelist **namelist, const char *str)
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

void		combine_path(char *dst, char *left, char *right)
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
