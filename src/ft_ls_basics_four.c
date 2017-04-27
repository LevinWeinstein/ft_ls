/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_basics_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 15:06:24 by lweinste          #+#    #+#             */
/*   Updated: 2017/04/26 14:13:22 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>
#include <ft_ls.h>

int				a_filter(t_ls_flags a, char *name)
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

t_ls			*single(t_ls_flags a, char *above, char *name)
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

int				ft_ls_namerr(char *name)
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

/*
** The LS distributed on OS X [including lab computers] uses the
** <fts.h> functions. When this happens, ls closes with the errno
** ENOENT, even though fts_open is not a file or directory. This is
** most likely due to fts_open returning an FTS*
*/

void			do_nothing(void)
{
	return ;
}
