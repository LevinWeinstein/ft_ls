/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   help_l.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 02:52:33 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/03 03:19:25 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ft_ls.h>
#include <libft.h>

char	get_mode(t_contents contents)
{
	mode_t	mode;

	mode = contents.stats->st_mode;
	if (S_ISBLK(mode))
		return ('b');
	if (S_ISCHR(mode))
		return ('c');
	if (S_ISDIR(mode))
		return ('d');
	if (S_ISSOCK(mode))
		return ('s');
	if (S_ISLNK(mode))
		return ('l');
	if (S_ISFIFO(mode))
		return ('p');
	if (S_ISREG(mode))
		return ('-');
	return ('X');
}

size_t	count_links(t_contents contents)
{
	return (0 + contents.stats->st_nlink);
}

char	*get_rights(t_contents contents)
{
	char	*output;
	mode_t	mode;

	mode = contents.stats->st_mode;
	output = ft_memalloc(10 * sizeof(char));
	output[0] = (mode & S_IRUSR) ? 'r' : '-';
	output[1] = (mode & S_IWUSR) ? 'w' : '-';
	if (mode & S_ISUID)
		output[2] = (mode & S_IXUSR) ? 's' : 'S';
	else
		output[2] = (mode & S_IXUSR) ? 'x' : '-';
	output[3] = (mode & S_IRGRP) ? 'r' : '-';
	output[4] = (mode & S_IWGRP) ? 'w' : '-';
	if (mode & S_ISGID)
		output[5] = (mode & S_IXGRP) ? 's' : 'S';
	else
		output[5] = (mode & S_IXGRP) ? 'x' : '-';
	output[6] = (mode & S_IROTH) ? 'r' : '-';
	output[7] = (mode & S_IWOTH) ? 'w' : '-';
	if (mode & S_ISVTX)
		output[8] = (mode & S_IXOTH) ? 't' : 'T';
	else
		output[8] = (mode & S_IXOTH) ? 'x' : '-';
	return (output);
}

char	*get_user(t_contents contents)
{
	char			*output;
	struct passwd	*tmp;

	tmp = getpwuid(contents.stats->st_uid);
	output = ft_strdup(tmp->pw_name);
	return (output);
}

char	*get_group(t_contents contents)
{
	char			*output;
	struct group	*tmp;

	tmp = getgrgid(contents.stats->st_gid);
	output = ft_strdup(tmp->gr_name);
	return (output);
}
