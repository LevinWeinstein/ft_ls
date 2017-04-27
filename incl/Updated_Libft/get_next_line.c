/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/27 13:32:33 by lweinste          #+#    #+#             */
/*   Updated: 2017/01/30 18:35:05 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	str_diff(char *big, char *little)
{
	return (ft_strlen(big) - ft_strlen(little));
}

static int	save_line(const int fd, char *buf, char *fd_lines[fd])
{
	int		cnt;
	char	*tmp;

	while (ft_strchr(buf, '\n') == NULL && (cnt = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[cnt] = '\0';
		tmp = fd_lines[fd];
		fd_lines[fd] = ft_strjoin(tmp, buf);
		ft_strdel(&tmp);
	}
	ft_strdel(&buf);
	if (cnt < 0)
		return (-1);
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	char		*buf;
	char		*full_line;
	char		*temp;
	static char *fd_lines[2147483647];
	int			count_read;

	buf = ft_strnew(BUFF_SIZE);
	if (fd < 0 || line == NULL || buf == NULL || BUFF_SIZE <= 0)
		return (-1);
	if (fd_lines[fd] == NULL)
		fd_lines[fd] = ft_strnew(1);
	if ((count_read = save_line(fd, buf, fd_lines)) == -1)
		return (-1);
	if ((full_line = ft_strchr(fd_lines[fd], '\n')) != NULL)
	{
		*line = ft_strndup(fd_lines[fd], str_diff(fd_lines[fd], full_line));
		temp = fd_lines[fd];
		fd_lines[fd] = ft_strdup(full_line + 1);
		ft_strdel(&temp);
		return (1);
	}
	*line = ft_strdup(fd_lines[fd]);
	fd_lines[fd] = NULL;
	return (ft_strlen(*line) > 0 ? 1 : 0);
}
