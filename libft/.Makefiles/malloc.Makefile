NAME = libft.a
LIBSO = $(NAME:%.a=%.so)
CC = clang
SRC =	malloc.c show_alloc.c zone.c\
		get.c allocation.c error.c\
		free.c realloc.c realloc_2.c\
		malloc_2.c log.c
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
