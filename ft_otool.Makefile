NAME = ft_otool
CC = clang
FLAGS = -Wall -Wextra -Werror -Ofast -O3
INC = include
INCLUDE = ft_otool.h
INCLUDES = $(INCLUDE:%.h=$(INC)/%.h)
SRC = src/ft_otool
OBJ = src/ft_otool_obj
SRCS =	ft_otool.c
OBJS = $(SRCS:%.c=$(OBJ)/%.o)
LIBFT = libft
INCLUDE_LIBS = -I $(LIBFT)/include
COMPILE_LIBS = -L $(LIBFT) -lft
N = 0
MAX = $(words $(OBJS))
JOBS = 4

.PHONY: all clean fclean re export

all: $(NAME)

$(OBJ):
	@mkdir $@

$(LIBFT)/libft.a:

$(OBJ)/%.o: $(SRC)/%.c $(INCLUDES) $(LIBFT)/libft.a | $(OBJ)
	@$(CC) $(FLAGS) -I $(INC) $(INCLUDE_LIBS) -o $@ -c $<
	@$(eval N=$(shell echo $$(($(N)+1))))
	@$(eval PERCENT=$(shell echo $$((($(N)*100)/$(MAX)))))
	@printf "\033[0m\033[38;5;124m[\033[38;5;7m%3u%% \033[38;5;124m$(NAME)] \033[38;5;207m🍇  $@ done\033[0m\n" $(PERCENT)

$(NAME): $(OBJS)
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(COMPILE_LIBS)
	@echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[38;5;125m🐼  $(NAME) done\033[0m"

clean:
	@rm -f $(OBJS)
	@echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[0m\033[38;5;87m$(NAME) removed\033[0m"

norme:
	@norminette $(OBJS:$(OBJ)/%.o=$(SRC)/%.c) $(INCLUDES)

re: fclean all
