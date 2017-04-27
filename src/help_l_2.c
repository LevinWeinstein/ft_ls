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

size_t		count_bytes(t_contents contents)
{
	return (0 + contents.stats->st_size);
}

int			print_year(time_t file)
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

char		*time_string(time_t file)
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

t_longform	*get_details(t_ls *home, t_contents contents)
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

size_t		longest_user(const t_contents *set)
{
	t_contents	*copy;
	size_t		longest;
	size_t		current;

	longest = 0;
	copy = (t_contents*)set;
	while (copy != NULL)
	{
		current = ft_strlen(copy->details->user);
		if (current > longest)
			longest = current;
		copy = copy->next;
	}
	return (longest);
}
