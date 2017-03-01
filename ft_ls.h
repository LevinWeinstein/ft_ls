#ifndef FT_LS_H
# define FT_LS_H
# include <dirent.h>
# include <errno.h>
# include <grp.h>
# include <pwd.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/syslimits.h>
# include <sys/types.h>
# include <sys/xattr.h>
# include <time.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

typedef struct s_longform	t_longform;
struct						s_longform{
	char					mode;
	size_t					links;
	char					*rights;
	char					*user;
	char					*group;
	size_t					bytes;
	char					*time;
};

typedef struct s_contents	t_contents;
struct						s_contents{
	char					*name;
	struct stat				*stats;
	t_longform				details;
	struct s_contents		*next;
};

typedef struct s_ls			t_ls;
struct						s_ls{
	char					*cur;
	DIR						*open;
	struct dirent			*ent;
	t_contents				*items;
	t_contents				*dirs;
	t_ls					*next;
};

# endif
