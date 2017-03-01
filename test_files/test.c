#include <unistd.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/syslimits.h>
#include <string.h>
#include <sys/types.h>
#include <pwd.h>
#include <grp.h>
#include <uuid/uuid.h> //<-- might not exist?
#include <sys/xattr.h>
#include <fcntl.h>
#include <time.h>
#include <errno.h>
#include <stdio.h>

void	ft_complain(void)
{
	printf("testo usage: ./testo [A FREAKIN DIRECTORY]\n");
	exit (-1);
}

void	say_the_prob(void)
{
	perror("testo");
	exit (-1);
}

int		main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *ent;
	ssize_t		size;
	struct stat deep;
	char		attributes[MAXNAMLEN + 1];

	if (argc != 2)
		ft_complain();
	errno = 0;
	if ((dir = opendir(argv[1])) == NULL)
		say_the_prob();
	while ((ent = readdir(dir)) != NULL)
	{
		lstat (ent->d_name, &deep);
		write(1, ent->d_name, (size_t)ent->d_namlen);
		ent->d_type = IFTODT(deep.st_mode);
		printf("\n%llu\n", ent->d_fileno);
		printf("%hu\n", ent->d_reclen);
		if (ent->d_type & DT_WHT && !(ent->d_type & DT_REG))
			ent->d_type & DT_DIR ? printf("DIR") : printf("CHR");
		else if (ent->d_type & DT_LNK || ent->d_type & DT_SOCK)
			ent->d_type & DT_SOCK ? printf("SOCK") : printf("LNK");
		else if (ent->d_type & DT_REG || ent->d_type & DT_BLK)
			ent->d_type & DT_REG ? printf("REG") : printf("BLOCK");
		else
			ent->d_type & DT_FIFO ? printf("FIFO") : printf("THE ABYSS OF IMPOSSIBILITY");
		putchar('\n');
		/*if (ent->d_type <= 1)
			ent->d_type == 0 ? printf("Unknown :o\n") : printf("FIFO!\n");
		else if (ent->d_type <= 4)
			ent->d_type == 2 ? printf("Special CHAR\n") : printf("It's a DIR!\n");
		else if (ent->d_type <= 8)
			ent->d_type == 6 ? printf("Special BLOCK\n") : printf("It's REGULAR!\n");
		else if (ent->d_type <= 12)
			ent->d_type == 10 ? printf("Is that zelda? Oh, whoops. I meant link.\n") : printf("Socks!\n");
		else if (ent->d_type == 14)
			printf("WHAT IS WHT????????\n");
		else
			printf("so this shouldn't happen...\n");*/
		/*if (listxattr(ent->d_name, attributes, MAXNAMLEN, 0) > 0) 
			printf("holy fuck there's attribz? Here: %s <-- :O DOOOOPE!\n", attributes);
		if (ent->d_type & DT_WHT)
			puts("nice!\n");*/
	}
	printf("Also: %d?", MAXNAMLEN);
	return (0);
}
		
