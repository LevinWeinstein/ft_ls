/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls_l.c                                          :+:      :+:    :+:   */
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
	return('X');
}

size_t	count_links(t_contents contents)
{
	return (0 + contents.stats->st_nlink);
}

char    *get_rights(t_contents contents)
{
	char *output;
	mode_t mode;
	
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

size_t	count_bytes(t_contents contents)
{
	return (0 + contents.stats->st_size);
}

int		print_year(time_t file)
{
	time_t	current;
	time_t	limit;
	time_t	difference;

	current = time(NULL);
	if (current == (time_t)-1)
		return (-1);
	limit = (time_t)(60 * 60 * 24 * 180);
	difference = (current - file);
	if (difference > limit || limit + difference < 0)
	   return (1);
	return (0);
}

char	*time_string(time_t file)
{
	char	**split;
	char	*temp;
	char	*temp2;
	char	*output;
	int		year;

	split = ft_strsplit(ctime(&file), ' ');
	output = ft_strjoin(split[1], " ");
	if (ft_strlen(split[2]) < 2)
		temp = ft_strjoin(" ", split[2]);
	else
		temp = ft_strdup(split[2]);
	temp2 = ft_strjoin(output, temp);
	free(output);
	free(temp);
	if ((year = print_year(file)) > 0)
		temp = ft_strjoin(temp2, "  ");
	else
		temp = ft_strjoin(temp2, " ");
	free(temp2);
	temp2 = ft_strndup(split[3 + year], 5 - year);
	output = ft_strjoin(temp, temp2);
	free(temp);
	free(temp2);
	return (output);
}

t_longform *get_details(t_ls *home, t_contents contents)
{
	t_longform	*output;
	char		*tmp1;
	char		*tmp2;
	struct stat	test;

	tmp1 = ft_strjoin(home->cur, "/");
	tmp2 = ft_strjoin(tmp1, contents.name);
	free(tmp1);
	if (lstat(tmp2, &test) == -1)
		return (NULL);
	//home->total += test.st_blocks;
	output = (t_longform*)malloc(sizeof(t_longform));
	output->mode = get_mode(contents);
	output->links = count_links(contents);
	output->rights = get_rights(contents);
	output->user = get_user(contents);
	output->group = get_group(contents);
	output->bytes = count_bytes(contents);
	output->time = time_string(contents.stats->st_mtime);
	free(tmp2);
	return (output);
}

/*
** CALCULATIONS ^v   ~~~~~~~~~~~ :o
** 
** We are currently between the two forms of calculations.
** Here we transition from storing 
etails of each individual 
** [up: details] - those calculations relating to "details" are above
** [down: fspec] - those calculations relating to format specification are below
*/

/*
** Calculations above ^^ , vv printing/formatting spaces below~~ :) !! <(")
*/

size_t	longest_user(const t_contents *set)
{
	t_contents *copy;
	size_t longest;
	size_t current;

	longest = 0;
	copy = (t_contents*)set;
	while(copy != NULL)
	{
		current = ft_strlen(copy->details->user);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}

size_t	longest_group(const t_contents *set)
{
	t_contents *copy;
	size_t longest;
	size_t current;
	
	longest = 0;
	copy = (t_contents*)set;
	while(copy != NULL)
	{
		current = ft_strlen(copy->details->group);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}

size_t	get_digits(size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (1);
	while(n != 0 && ++i)
		n /= 10;
	return (i);
}

size_t	link_digits(const t_contents *set)
{
	t_contents *copy;
	size_t		longest;
	size_t		current;

	longest = 0;
	copy = (t_contents*)set;
	while(copy != NULL)
	{
		current = get_digits(copy->details->links);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}

size_t	byte_digits(const t_contents *set)
{
	t_contents *copy;
	size_t		longest;
	size_t		current;

	longest = 0;
	copy = (t_contents*)set;
	while(copy != NULL)
	{
		current = get_digits(copy->details->bytes);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}

void	check_link(t_ls *home, t_contents check)
{
	char	linked_from[PATH_MAX + 1];
	char	linked_to[PATH_MAX + 1];

	if ((S_ISLNK(check.stats->st_mode)))
	{
		ft_bzero(linked_to, PATH_MAX + 1);
		ft_bzero(linked_from, PATH_MAX + 1);
		combine_path(linked_from, home->cur, check.name);
		//temp = ft_strjoin(home->cur, "/");
		//temp2 = ft_strjoin(temp, check.name);
		//free(temp);
		readlink(linked_from, linked_to, PATH_MAX + 1);
		ft_putstr(" -> ");
		ft_putstr(linked_to);
		//free(temp2);
	}
	ft_putchar('\n');
}

void	ft_putspace(char *str)
{
	ft_putstr(str);
	ft_putchar(' ');
}

void	ft_charstr(char c, char *str)
{
	ft_putchar(c);
	ft_putstr(str);
}

void	ft_numspace(int n)
{
	ft_putnbr(n);
	ft_putchar(' ');
}

/*
** To migrate to w, replace putprint in names to putstr
*/
void	ft_putprint(const char *str)
{
	int	i;
	char c;

	i = -1;
	while((c = str[++i]) != '\0')
		ft_putchar(ft_isprint(c) > 0 ? c : '?');
}

void	grab_name(t_ls *home, t_contents *contents)
{
	size_t	i;
	size_t	j;
	char	*str;

	if (home == NULL || home->cur == NULL ||
			contents == NULL || contents->name == NULL)
		return ;
	j = ft_strlen(contents->name) - 1;
	i = j;
	while(i > 0 && contents->name[i] != '\\')
		i--;
	j -= i - 1;
	str = ft_strndup(contents->name + i, j);
	ft_putprint(str);
	ft_strdel(&str);
}

void	ok_putnbr(intmax_t n)
{
	int	negative;

	if((negative = (n < 0 ? -1 : 1)) == -1)
		ft_putchar('-');
	if (n > 10 || n < -10)
		ok_putnbr((n / 10) * negative);
	ft_putchar('0' + ((n % 10) * negative));
}

void	print_total(long long blocks)
{
	ft_putstr("total ");
	ok_putnbr(blocks);
	ft_putchar('\n');
}

void	print_long(t_ls *home, t_contents *safe, t_contents *set)
{
	size_t	i;
	
	i = 0;
	if (set == NULL || set->details == NULL)
		return ;
	ft_charstr(set->details->mode, set->details->rights);
	while(i++ <= 1 + (link_digits(safe) - get_digits(set->details->links)))
		ft_putchar(' ');
	ft_putnbr((i = 0) < 2 ? (int)set->details->links: 0);
	while(i++ <= longest_user(safe) - ft_strlen(set->details->user))
		ft_putchar(' ');
	ft_putstr((i = 0) < 2 ? set->details->user : "?\0");
	while(i++ <= 1 + longest_group(safe) - ft_strlen(set->details->group))
		ft_putchar(' ');
	ft_putstr((i = 0) < 1 ? set->details->group : "?\0");
	while(i++ <= 1 + byte_digits(safe) - get_digits(set->details->bytes))
		ft_putchar(' ');
	ft_numspace(set->details->bytes);
	ft_putspace(set->details->time);
	grab_name(home, set);
	check_link(home, *set);
	print_long(home, safe, set->next);
}



