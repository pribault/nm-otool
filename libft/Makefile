NAME = libft.a
LIBSO = $(NAME:%.a=%.so)
CC = clang
JOINF_SRC =	ft_joinf.c ft_printj.c\
			number_join.c string_join.c\
			unsigned_join.c
PRINTF_SRC =	char.c ft_printf.c\
				if_forest.c long.c\
				number.c other.c\
				params.c pointer.c\
				string.c unsigned.c
LIBFT_SRC =	ft_abs.c\
			ft_add_errors.c\
			ft_alloc_array.c\
			ft_arraylen.c\
			ft_atoi.c\
			ft_atou.c\
			ft_atof.c\
			ft_bzero.c\
			ft_error.c\
			ft_execute.c\
			ft_factorial.c\
			ft_free_array.c\
			ft_get_all_lines.c\
			ft_get_file_name_from_path.c\
			ft_get_flag_array.c\
			ft_get_flags.c\
			ft_get_next_line.c\
			ft_getenv.c\
			ft_implode.c\
			ft_isalnum.c\
			ft_isalpha.c\
			ft_isascii.c\
			ft_isdigit.c\
			ft_isfloat.c\
			ft_isinteger.c\
			ft_isnumeric.c\
			ft_isprime.c\
			ft_isprint.c\
			ft_isunsigned.c\
			ft_itoa.c\
			ft_ls.c\
			ft_lstadd.c\
			ft_lstdel.c\
			ft_lstdelone.c\
			ft_lstget.c\
			ft_lstiter.c\
			ft_lstlen.c\
			ft_lstmap.c\
			ft_lstmove.c\
			ft_lstnew.c\
			ft_lstprint.c\
			ft_lstput.c\
			ft_lstsort.c\
			ft_memalloc.c\
			ft_memccpy.c\
			ft_memchr.c\
			ft_memcmp.c\
			ft_memcpy.c\
			ft_memdel.c\
			ft_memdump.c\
			ft_memdup.c\
			ft_memmove.c\
			ft_memset.c\
			ft_mod.c\
			ft_multisplit.c\
			ft_nbrlen.c\
			ft_power.c\
			ft_putchar.c\
			ft_putchar_fd.c\
			ft_putendl.c\
			ft_putendl_fd.c\
			ft_putnbr.c\
			ft_putnbr_fd.c\
			ft_putstr.c\
			ft_putstr_fd.c\
			ft_rand.c\
			ft_showtab.c\
			ft_showtab_fd.c\
			ft_sqrt.c\
			ft_strcat.c\
			ft_strchr.c\
			ft_strclr.c\
			ft_strcmp.c\
			ft_strcpy.c\
			ft_strdel.c\
			ft_strdup.c\
			ft_strequ.c\
			ft_striter.c\
			ft_striteri.c\
			ft_strjoin.c\
			ft_strlcat.c\
			ft_strlen.c\
			ft_strmap.c\
			ft_strmapi.c\
			ft_strncat.c\
			ft_strncmp.c\
			ft_strncpy.c\
			ft_strndup.c\
			ft_strnequ.c\
			ft_strnew.c\
			ft_strnstr.c\
			ft_strrchr.c\
			ft_strsplit.c\
			ft_strstr.c\
			ft_strsub.c\
			ft_strtrim.c\
			ft_swap.c\
			ft_tolower.c\
			ft_toupper.c\
			ft_vector_add.c\
			ft_vector_del.c\
			ft_vector_del_one.c\
			ft_vector_get.c\
			ft_vector_new.c\
			ft_vector_printhex.c\
			ft_vector_resize.c
MALLOC_SRC =	malloc.c allocation.c\
				show_alloc.c realloc.c\
				free.c sort.c\
				malloc_error.c
SRC =	$(LIBFT_SRC:%.c=libft/%.c)\
		$(PRINTF_SRC:%.c=ft_printf/%.c)\
		$(JOINF_SRC:%.c=ft_joinf/%.c)\
		$(MALLOC_SRC:%.c=malloc/%.c)
OBJ = $(SRC:%.c=obj/%.o)
OBJ_DIR = obj/libft obj/ft_printf obj/ft_joinf obj/malloc
FLAGS = -Wall -Wextra
INCLUDES =	libft.h ft_printf.h ft_joinf.h malloc.h prototypes.h structs.h
INCLUDE = $(INCLUDES:%.h=include/%.h)

.PHONY: clean fclean all re norme

all: $(NAME)

obj:
	@if ! [ -d obj ]; then mkdir obj; fi

$(OBJ_DIR): | obj
	@if ! [ -d obj/libft ]; then mkdir obj/libft; fi
	@if ! [ -d obj/ft_printf ]; then mkdir obj/ft_printf; fi
	@if ! [ -d obj/ft_joinf ]; then mkdir obj/ft_joinf; fi
	@if ! [ -d obj/malloc ]; then mkdir obj/malloc; fi

obj/%.o: src/%.c $(INCLUDE) | $(OBJ_DIR)
	@echo "\033[0m🌶  \033[38;5;226mmaking $@\033[0m"
	@$(CC) $(FLAGS) -fPIC -I include -o $@ -c $<

$(LIBSO): $(OBJ)
	@echo "\033[0m🦁  \033[38;5;214mmaking $@\033[0m"
	@$(CC) $(FLAGS) -shared -o $(LIBSO) $(OBJ)

$(NAME): $(OBJ)
	@echo "\033[0m🐹  \033[38;5;214mmaking $@\033[0m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

clean:
	@echo "\033[0m\033[38;5;45mremoving object files\033[0m"
	@rm -rf obj

fclean: clean
	@echo "\033[0m\033[38;5;87mremoving $(NAME) and $(LIBSO)\033[0m"
	@rm -f $(NAME)
	@rm -f $(LIBSO)

norme:
	@norminette $(OBJ:obj/%.o=src/%.c) $(INCLUDE)

re: fclean all
