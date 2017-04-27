NAME = ft_ls

DIRECTORY = ./
AND_GLOBAL_HEADERS = -I ./incl/
CLIBFT = Updated_Libft/
CFILES = ft_ls_basics_one.c ft_ls_basics_two.c ft_ls_basics_three.c ft_ls_basics_four.c ft_ls_basics_five.c ft_ls_basics_six.c help_l.c \
		 help_l_2.c help_l_3.c help_l_4.c help_l_5.c ft_ls.c ft_ls_l.c
LIBFT = $(addprefix ./incl/, $(CLIBFT))
LIBNAME = libft.a
COMPILE = @gcc
THIS_PROGRAM = -o $(NAME)
WITH_FLAGS = -Wall -Wextra -Werror
AND_FILES = $(addprefix ./src/, $(CFILES))
LINKED_TO_LIBFT  = -I $(LIBFT) -L $(LIBFT) -lft

MADE_LIBFT = $(addprefix $(LIBFT), $(LIBNAME))

all:
	@if test ! -f $(NAME); then \
		rm $(MADE_LIBFT); \
		Make -C $(LIBFT); \
		make _all; \
	else \
		echo "\x1b[96mA version of ft_ls has already been created"; \
	fi
	@echo "\x1b[0mEnding..."
_all: $(NAME)
	@echo "\x1b[96m\t[\x1b[33m\x1b[4mft_ls\x1b[24m\x1b[21m\x1b[96m]:\x1b[21m\x1b[32mCompilation Complete."

$(NAME):
	$(COMPILE) $(THIS_PROGRAM) $(WITH_FLAGS) $(AND_FILES) $(AND_GLOBAL_HEADERS) $(LINKED_TO_LIBFT)
clean:
	@Make clean -C $(LIBFT)
fclean:
	@Make fclean -C $(LIBFT)
	rm -f $(NAME)
re: fclean all
