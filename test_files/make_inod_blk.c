/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_inod_blk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 14:01:29 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/01 15:22:58 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <errno.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

#define _POSIX_C_SOURCE
#define _DARWIN_C_SOURCE
#define _NONSTD_SOURCE
#include <sys/cdefs.h>

int		main(void)
{
	int	fd;
	char *str;
	struct stat stats;

	printf("%s\n", __STRING(723));
	const char *noconst;
	srand(time(NULL));
	lstat(".", &stats);
	errno = 0;
	if (asprintf(&str, "./%u", arc4random()) < 0)
		perror("RandoFifo:");
	printf(str);
	return (mknod(str, S_IFIFO, 0) == -1) ? -1 : 0;
}
