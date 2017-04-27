LIBNAME = libft.a

DIRECTORY = ./

CC = @gcc

CFLAGS = -c -Wall -Wextra -Werror

CFILES = ft_atoi.c ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c ft_memalloc.c ft_memccpy.c ft_memchr.c ft_memcmp.c ft_memcpy.c ft_memdel.c ft_memmove.c ft_memset.c ft_strcat.c ft_strchr.c ft_strcmp.c ft_strcpy.c ft_strdup.c ft_strlcat.c ft_strlen.c ft_strncat.c ft_strncmp.c ft_strncpy.c ft_strnstr.c ft_strrchr.c ft_strstr.c ft_tolower.c ft_toupper.c ft_strnew.c ft_strdel.c ft_strclr.c ft_striter.c ft_striteri.c ft_strmap.c ft_strmapi.c ft_strequ.c ft_strnequ.c ft_strsub.c ft_strjoin.c ft_strtrim.c ft_strsplit.c ft_itoa.c ft_putchar.c ft_putstr.c ft_putendl.c ft_putnbr.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_lstnew.c ft_lstdelone.c ft_lstdel.c ft_lstadd.c ft_lstiter.c ft_lstmap.c ft_strndup.c ft_itoa_base.c ft_utoa_base_lower.c ft_utoa_base_upper.c get_next_line.c

OBJECTS = ft_atoi.o ft_bzero.o ft_isalnum.o ft_isalpha.o ft_isascii.o ft_isdigit.o ft_isprint.o ft_memalloc.o ft_memccpy.o ft_memchr.o ft_memcmp.o ft_memcpy.o ft_memdel.o ft_memmove.o ft_memset.o ft_strcat.o ft_strchr.o ft_strcmp.o ft_strcpy.o ft_strdup.o ft_strlcat.o ft_strlen.o ft_strncat.o ft_strncmp.o ft_strncpy.o ft_strnstr.o ft_strrchr.o ft_strstr.o ft_tolower.o ft_toupper.o ft_strnew.o ft_strdel.o ft_strclr.o ft_striter.o ft_striteri.o ft_strmap.o ft_strmapi.o ft_strequ.o ft_strnequ.o ft_strsub.o ft_strjoin.o ft_strtrim.o ft_strsplit.o ft_itoa.o ft_putchar.o ft_putstr.o ft_putendl.o ft_putnbr.o ft_putchar_fd.o ft_putstr_fd.o ft_putendl_fd.o ft_putnbr_fd.o ft_lstnew.o ft_lstdelone.o ft_lstdel.o ft_lstadd.o ft_lstiter.o ft_lstmap.o ft_strndup.o ft_itoa_base.o ft_utoa_base_lower.o ft_utoa_base_upper.o get_next_line.o

FILES = $(addprefix $(DIRECTORY), $(CFILES))
all:
	@echo "\t\x1b[96m\x1b[1mCompiling Library:\x1b[0m\x1b[96m [\x1b[93m\x1b[4mlibft.a\x1b[24m\x1b[96m]"
	@if test ! -f $(LIBNAME); then \
		make innerall; \
	else \
		echo "\t\x1b[33mlibft.a Already Made!"; \
	fi

innerall: $(LIBNAME)

$(LIBNAME): $(OBJECTS)
	@echo "\x1b[96m\t[\x1b[33m\x1b[4mLibft\x1b[24m\x1b[96m]:\x1b[32mLibft: Libft: Turning Objects Into Library"
	@ar rc $(LIBNAME) $(OBJECTS)
	@echo "\x1b[96m\t[\x1b[33m\x1b[4mLibft\x1b[24m\x1b[96m]:\x1b[21m\x1b[32mLibft: Optimizing... (ranlib)"
	@ranlib $(LIBNAME)
	@echo "\x1b[96m\t[\x1b[33m\x1b[4mLibft\x1b[24m\x1b[21m\x1b[96m]:\x1b[21m\x1b[32mLibft: libft.a Complete!"


$(OBJECTS): $(SRCFILES)
	@echo "\x1b[96m\t[\x1b[33m\x1b[4mLibft\x1b[24m\x1b[96m]:\x1b[21m\x1b[32m Building Objects From Source\x1b[21m"
	$(CC)  $(CFLAGS) $(CFILES) -I ./libft.h
	@if test ! -f $(OBECTS); then\
		echo "Compilation Failure"; \
	else \
		echo "\x1b[96m\t[\x1b[33m\x1b[4mLibft\x1b[24m\x1b\x1b[96m]:\x1b[21m\x1b[32m Objects Compiled\x1b[21m"; \
	fi

clean: 	
	@/bin/rm -f $(OBJECTS)
	@echo "\x1b[96m\t[\x1b[33m\x1b[4mLibft\x1b[24m\x1b[21m\x1b[96m]\x1b[21m\x1b[32m clean Complete."
fclean: clean
	@/bin/rm -f $(LIBNAME)
	@echo "\x1b[96m\t[\x1b[33m\x1b[4mLibft\x1b[24m\x1b[21m\x1b[96m]\x1b[21m\x1b[32m fclean Complete."
re:	fclean all
.PHONY: clean fclean re all
