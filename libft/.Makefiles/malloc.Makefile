NAME = libft.a
LIBSO = $(NAME:%.a=%.so)
CC = clang
SRC =	malloc.c allocation.c\
		show_alloc.c realloc.c\
		free.c sort.c\
		malloc_error.c
DIR = malloc
SRC_DIR = src
OBJ_DIR = .obj
OBJ = $(SRC:%.c=$(OBJ_DIR)/$(DIR)/%.o)
FLAGS = -Wall -Wextra -Werror
INCLUDES =	malloc.h prototypes.h structs.h
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
	@printf "\033[0m\033[38;5;12m[\033[38;5;7m%3u%% \033[38;5;12m$(DIR)] \033[0m🌶  \033[38;5;226m$(@:$(OBJ_DIR)/$(DIR)/%.o=%.o) done\033[0m\n" $(PERCENT)

$(NAME): $(OBJ)
	@if [ ! $(N) = 0 ]; then ar rc $(NAME) $(OBJ); ranlib $(NAME); echo "\033[0m\033[38;5;12m[∎∎∎∎ $(DIR)] \033[0m🐹  \033[38;5;214m$@ done\033[0m"; fi

clean:
	@rm -rf $(OBJ_DIR)/$(DIR)
	@echo "\033[0m\033[38;5;12m[∎∎∎∎ $(DIR)] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;12m[∎∎∎∎ $(DIR)] \033[0m\033[38;5;87m$(NAME) and $(LIBSO) removed\033[0m"

norme:
	@norminette $(OBJ:$(OBJ_DIR)/%.o=$(SRC_DIR)/%.c) $(INCLUDE)

re: fclean all
