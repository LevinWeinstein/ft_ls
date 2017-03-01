/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lweinste <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 08:45:46 by lweinste          #+#    #+#             */
/*   Updated: 2017/03/01 09:48:41 by lweinste         ###   ########.fr       */
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

typedef struct s_ls			t_ls;
struct						s_ls{
	char					*cur;
	DIR						*open;
	struct dirent			*ent;
	t_contents				*items;
	t_contents				*dirs;
	t_ls					*next;
};
/*
** Longform Functions
*/
char						get_mode(t_contents contents);
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
void						print_long(t_ls *home, t_contents *safe, t_contents *set);

/*
** 		2. Normal Print Functions								
*/
void						ft_putstr_nl(char *str);
void						name_error(char *filename);
void						print_items(t_contents *contents);
void						print_visible(t_contents *contents);
void						print_named(t_contents *contents);

/*
** 		3. _ls Functions												----II.3
*/

t_ls						*noname_ls(void);
t_ls						*single(char *above, char *name);

/*
**  	4. _contents Functions											----II.4
*/
t_contents					*new_link(char *str);//potentially unused;
void						print_contents(t_ls *cur, t_contents *contents);
void						swap_contents(t_contents *one, t_contents *two);
void						sort_contents(t_contents **contents);
void						revsort_contents(t_contents **contents);
t_contents					*new_item(t_ls *ls, struct dirent *ent);

/*
**		5.	Adding Functions which have confusing names so I explain which is which.
** 				a. ls_add_back: add an individual link to the back of an LS struct
*/
void						ls_add_back(t_ls **ls, t_ls *add);
/*
** 				b. ls_add_item: add an individual link to the back of a CONTENTS struct
*/
void						ls_add_item(t_contents **ls, t_contents *add);


# endif































/*   NOTES
** Structures: t_ls holds the contents of an individual ls argument or recursion,
**			   With the argument's name stored in "char *cur", an open DIR named
**			   DIR *open to be used by functions who would like to read the contents
**			   of the searched area, and a struct dirent *ent for open to read into.
**			   t_ls holds two sets of contents, one which holds every element within
**			   the directory, and one that specifically stores subdirectories in anticipation
**			   of ls -R.
**
**			   t_contents is what stores the items and dirs from t_ls. within an element,
**			   there is it's name, it's stats, and a t_longform with ls -l details.
**			   
**				t_longform: the ls manual described "The Long Format" as displaying for
**				each file the following:
**						File Mode, Number of Links, Owner Name, Group Name, Number of Bytes in the File,
**						Abbreviated Month, day-of-month file was last modified, hous file last modified,
**						minute file last modified, and pathname.
**
**						IN ADDITION, for each directory whose contents are displayed, the total number
**						of 512-byte blocks used by the files in the directory is displayed on a line
**						by itself, immediately before the information for the files in the directory.
**
**						[bonus]If the file of directory has extended attributes, the permissions field
**						printed by the -l option is followed by a '@' character. Otherwise, if the file
**						or directory has extended secutiry information (such as an access control list),
**						the permissions field printed by the -l option is followed by a '+' character.
**
**						If the modification time of the file is more than 6 months in the past or future
**						[180 days], then the year of the last modification is displayd in place of the
**						hour and minute fields.
**
**						If the file is a character special or block special file, the major and minor
**						device numbers for the file are displayed in the size field. If the file is a
**						symbolic link, the path-name of the linked-to file is preceded by "->".
**
**			Careful:
**						The manual clearly states that the 'x' box in the permissions is set to the
**						FIRST of the following that applies:
**
**						   *S: If in the owner permissions, the file IS NOT executable and set-user-ID mode is set.	
**						  **s: If in the owner permissions, the file IS  	executable and set-user-ID mode is set.
**						 ***x: The file is executable or the directory is searchable.
**						****-: The file is neither readable, writable, executable, nor set-user-ID not set-group-ID mode,
**									NOR STICKY.... [see below.]
**
**		T and t: "other" permissions exclusives
**						
**							*T:	The sticky bit is set (mode 1000), but not execute or search permission.
**							*t: The sticky bit is set (mode 1000), and is searchable or executable.
**
**	EV Prereq: -F, -G
**			
**	-F:		Display a slash immediately after each pathname that is a directory, an asterisk after each that is executable,
**			an @ sign after each symbolic link, an equals sign ('=') after each socket, a percent sign ('%') after each whiteout,
**			and a vertical bar ('|') after each that is FIFO.
**
**	-G:		Enable colorized output. This option is equivalent to defining CLICOLOR in the environment (see below).
**
**	ENVIRONMENT VARIABLES AFFECT LS [prereq: -F(just above)]
**			BLOCKSIZE:	   -If set, blocks are displayed in BLOCKSIZE sized blocks [instead of standard 512 byte blocks]
**			CLICOLOR :	   -Use	ANSI color sequences to distinguish file type. See LSCOLORS below. In addition to types
**							mentioned by -F (above), some extra attribute (setuid bit set, etc.) are also displayed. The
**							colorization is dependent on a terminal type with the proper termcap(5_ capabilities. The
**							default ''cons25'' console has the proper capabilities, but to display the colors in an xterm(1),
**							for example, the TERM variable must be set to "xterm-color". Other terminal types may require
**							similar adjustments. Colorization is silently disabled if the output isn't directed to a terminal
**							unless the CLICOLOR_FORCE variable if defined.
**		CLICOLOR_FORCE:	   -Color sequences are normally disabled if the output isn't directed to a terminal. This can be
**							overridden by setting this flag. The TERM variable still needs to reference a color capable
**							terminal however otherwise it is not possible to determin which color sequences to use.
**
**			COLUMNS  :		If this variable contains a string representing a decimal integer, it is used as the column
**							position width for displaying multiple-text-column output. The ls utility calculates how many
**							pathname text columns to display based on the width provided.
**
**			LANG	 :		The locale to use when determining the order of day and month in the long -l format output.
**							see environ(7) for more information.
**
**			LSCOLORS :		The value of this variable describes what colore to use for which attribute when colors are
**							enabled with CLICOLOR. This string is a concatenation of pairs of the format fb, where f is
**							the foreground color and b is the background color.
**
**						The color designators are as follows:
**						a black
**						b red
**						c green
**						d brown
**						e blue
**						f magenta
**						g cyan
**						h light grey
**						A bold black, usually shows up as dark grey.
**						B bold red
**						C bold green
**						D bold brown, usually shows up as yellow
**						E bold blue
**						F bold magenta
**						G bold cyan
**						H bold light grey; looks like bright white
**						x default foreground or background
**				
**			THEIR NOTE: ...these are standard ansi colors... somethin somethin
**			MY 	  NOTE: You're gonna put a macro for every single one of these
**						in your header file and they're gonna be hella fuckin
**						pretty. Rainbows make the pain go.
**
**			BUT HOLD UP I DON'T EVEN KNOW THE STRING FORMAT YET.
**			READ MORE.
**
**				The order of the attributes are as follows (with that two-char fb for each)
**				1. directory
**				2. symbolic link
**				3. socket.
**				4. pipe.
**				5. executable
**				6. block special
**				7. char  special
**				8 executable with setuid bit set
**				9. executable with setgid bit set
**			   10. directory writable to others, with 	 sticky bit
**			   11. directory writable to others, without sticky bit
**
**
**				THE DEFAULT IS (example!) "exfxcxdxbxegedabagacad"
**				so:
**				1. ex :: blue/default normal dirs
**				2. fx :: magenta/default sym-links
**				3. cx :: green/default sockets
**				4. dx :: brown/default pipes
**				5. bx :: red/default executable
**				6. eg :: blue/cyan block special
**				7. ed :: blue/brown char special
**				8. ab :: black/red  executable with setuid bit set
**				9. ag :: black/cyan executable with setgid bit set
**			   10. ac :: black/green directory writeable to others without sticky bit 
**			   11. ad :: black/blue directory writeable to others with sticky bit
**
**
**	 LS_COLWIDTHS	If this variable is set, it is considered to be a colon-delimited list of minimum column widths. 
**	Unreasonable and insufficient widths are ignored (thus zero signifies a dynamically sized columns). Not all columns
**	have changeable widths. The fields are, in order: -inode, -block count, -number of links, uder name, group name, flags,
**	file size, file name.
**
**	TERM			The CLICOLOR functionality depends on a terminal type with color capabilities
**	TZ				The timezone to use when displaying dates. See environ(7) for more information.
**						
*/

/*
** Lategame in a nutshell: need to learn environ and add colors.
** 						   Also need to read block size from environment.
** Early game: add block size after dirs in general.
*/
