/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 08:45:46 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/03 06:31:09 by lweinste         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

# define CAT(a, ...) PRIMITIVE_CAT(a, __VA_ARGS__)
# define PRIMITIVE_CAT(a, ...) a ## __VA_ARGS__
# define UNUSEDRETURN 0
# define ONLYFLAGS -42
# define PLS(ND) print_long_single(ND, ND)
# define PL(HB, ND) print_long(HB, ND, ND)
# ifndef STRINGIFY
#  define STRINGIFY(x) #x
# endif
# define SLSNM struct s_ls_namelist

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
	t_longform				*details;
	struct s_contents		*next;
};

typedef struct				s_ls_namelist{
	char					name[PATH_MAX + 1];
	SLSNM					*next;
}							t_ls_namelist;

typedef struct s_ls			t_ls;
struct						s_ls{
	char					*cur;
	DIR						*open;
	struct dirent			*ent;
	int						dcnt;
	blkcnt_t				total;
	struct stat				stats;
	t_contents				*items;
	t_contents				*dirs;
	t_ls_namelist			*namelist;
	t_ls					*next;
};

typedef struct s_ls_flags	t_ls_flags;
struct						s_ls_flags{
	int						aa;
	int						rr;

	int						a;
	int						l;
	int						r;
	int						t;
	int						one;
};

/*
** Longform Functions
*/

char						get_mode(t_contents contents);
void						check_link_single(t_contents check);
size_t						count_links(t_contents contents);
char						*get_rights(t_contents contents);
char						*get_user(t_contents contents);
char						*get_group(t_contents contents);
size_t						count_bytes(t_contents contents);
int							print_year(time_t file);
char						*time_string(time_t file);
t_longform					*get_details(t_ls *home, t_contents contents);
size_t						longest_user(const t_contents *set);
size_t						longest_group(const t_contents *set);
size_t						get_digits(size_t n);
size_t						link_digits(const t_contents *set);
size_t						byte_digits(const t_contents *set);
void						check_link(t_ls *home, t_contents check);
void						ft_putspace(char *str);
void						ft_charstr(char c, char *str);
void						ft_numspace(int n);
void						print_long(t_ls *home, t_contents *safe,
										t_contents *set);
void						print_long_single(t_contents *safe,
										t_contents *set);

/*
** 		2. Normal Print Functions
*/

void						grab_name(t_ls *home, t_contents *contents);
t_ls_namelist				*ls_readout(char *cur, const t_contents *items);
void						ft_putstr_nl(const char *str);
void						ft_putprint(const char *str);
void						name_error(char *filename);
void						print_items(t_contents *contents);
void						print_visible(t_contents *contents);
void						print_named(t_contents *contents);
void						print_total(long long blocks);
void						combine_path(char *dst, char *left, char *right);
t_ls_namelist				*clean_dots(t_ls_namelist *namelist,
										t_ls_flags flags);
int							ls_add_namelist(t_ls_namelist **namelist,
										const char *str);
int							get_flags(int argc, char **argv, t_ls_flags *flag);
void						ft_dirprint(const char *str);

/*
** 		3. _ls Functions												----II.3
*/

t_ls						*noname_ls(void);
t_ls						*single(t_ls_flags a, char *above, char *name);

/*
**  	4. _contents Functions											----II.4
*/

void						print_contents(t_ls *cur, t_contents *contents);
void						swap_contents(t_contents *one, t_contents *two);

void						sort_contents(t_contents **contents);
void						reverse_contents(t_contents **contents);
void						time_sort(t_contents **contents);
t_ls_namelist				*inner(t_ls_flags flags, char *dirname);
int							empty_flags(t_ls_flags *premade);
t_ls_namelist				*from_argv(int index, int argc, char **argv);
t_contents					*new_item(t_ls *ls, struct dirent *ent);
int							only_one(t_ls_namelist *namelist);
void						ls_add_item(t_contents **ls, t_contents *add);
t_longform					*get_details_single(t_contents contents);
int							ft_ls_namerr(char *name);
void						do_nothing(void);

#endif
