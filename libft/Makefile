NAME = libft.a
NAME_SO = $(NAME:%.a=%.so)
CC = gcc
FLAGS = -Wall -Wextra -Werror
LIBFT = libft
MALLOC = malloc
FT_PRINTF = ft_printf
FT_JOINF = ft_joinf
DIR = .Makefiles
EXT = Makefile
JOBS = 4

.PHONY: clean fclean all re norme $(NAME)

all: $(NAME)

$(NAME):
	@make -f $(DIR)/$(LIBFT).$(EXT) $(NAME) -j$(JOBS)
	@make -f $(DIR)/$(MALLOC).$(EXT) $(NAME) -j$(JOBS)
	@make -f $(DIR)/$(FT_PRINTF).$(EXT) $(NAME) -j$(JOBS)
	@make -f $(DIR)/$(FT_JOINF).$(EXT) $(NAME) -j$(JOBS)

$(NAME_SO): $(NAME)
	@$(CC) $(FLAGS) -shared -o $@ -L . -lft
	@echo "\033[0m\033[38;5;12m[∎∎∎∎ $($@)] \033[0m🦁  \033[38;5;214m$@ done\033[0m"

clean:
	@make -f $(DIR)/$(LIBFT).$(EXT) clean
	@make -f $(DIR)/$(MALLOC).$(EXT) clean
	@make -f $(DIR)/$(FT_PRINTF).$(EXT) clean
	@make -f $(DIR)/$(FT_JOINF).$(EXT) clean

fclean:
	@rm -f $(NAME)
	@rm -f $(NAME_SO)
	@rm -rf .obj

norme:
	@make -f $(DIR)/$(LIBFT).$(EXT) norme
	@make -f $(DIR)/$(MALLOC).$(EXT) norme
	@make -f $(DIR)/$(FT_PRINTF).$(EXT) norme
	@make -f $(DIR)/$(FT_JOINF).$(EXT) norme

re: fclean all
