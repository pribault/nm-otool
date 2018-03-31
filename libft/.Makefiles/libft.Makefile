NAME = libft.a
CC = clang
SRC =	ft_abs.c\
		ft_add_errors.c\
		ft_alloc_array.c\
		ft_arraylen.c\
		ft_atoi.c\
		ft_atou.c\
		ft_atof.c\
		ft_bzero.c\
		ft_circ_buffer_del.c\
		ft_circ_buffer_dequeue.c\
		ft_circ_buffer_enqueue.c\
		ft_circ_buffer_get_size.c\
		ft_circ_buffer_get.c\
		ft_circ_buffer_init.c\
		ft_circ_buffer_set_trash_callback.c\
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
		ft_reduce_path.c\
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
		ft_vector_init.c\
		ft_vector_printhex.c\
		ft_vector_resize.c
DIR = libft
SRC_DIR = src
OBJ_DIR = .obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/$(DIR)/%.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES =	libft.h
INCLUDE = $(INCLUDES:%.h=include/%.h)
N = 0
MAX = $(words $(OBJ))

.PHONY: clean fclean all re norme $(NAME)

.SILENT:

all: $(NAME)

$(OBJ_DIR):
	@mkdir $@

$(OBJ_DIR)/$(DIR): | $(OBJ_DIR)
	@mkdir $@

$(OBJ_DIR)/$(DIR)/%.o: $(SRC_DIR)/$(DIR)/%.c $(INCLUDE) | $(OBJ_DIR)/$(DIR)
	@$(CC) $(FLAGS) -fPIC -I include -o $@ -c $<
	@$(eval N=$(shell echo $$(($(N)+1))))
	@$(eval PERCENT=$(shell echo $$((($(N)*100)/$(MAX)))))
	@printf "\033[0m\033[38;5;166m[$(DIR) \033[38;5;7m%3u%%\033[38;5;166m] \033[0m🌶  \033[38;5;226m$(@:$(OBJ_DIR)/$(DIR)/%.o=%.o) done\033[0m\n" $(PERCENT)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@if [ ! $(N) = 0 ]; then echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m🐹  \033[38;5;214m$@ done\033[0m"; else echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m🐹  \033[38;5;214mnothing to be done\033[0m"; fi

clean:
	@rm -rf $(OBJ_DIR)/$(DIR)
	@echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;166m[$(DIR) ∎∎∎∎] \033[0m\033[38;5;87m$(NAME) and $(LIBSO) removed\033[0m"

norme:
	@norminette $(OBJ:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.c) $(INCLUDE)

re: fclean all
