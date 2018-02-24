NAME = ft_nm
CC = clang
FLAGS = -Wall -Wextra -Ofast -O3
INC = include
INCLUDE = ft_nm.h
INCLUDES = $(INCLUDE:%.h=$(INC)/%.h)
OBJ = src/ft_nm_obj
SRC = src/ft_nm
SRCS =	ft_nm.c flags.c endian.c\
		fat.c mach.c archive.c\
		get.c get_2.c get_3.c\
		symtab.c output.c segment.c\
		debug.c symbol.c
OBJS = $(SRCS:%.c=$(OBJ)/%.o)
LIBFT = libft
INCLUDE_LIBS = -I $(LIBFT)/include
COMPILE_LIBS = -L $(LIBFT) -lft
N = 0
MAX = $(words $(OBJS))
JOBS = 4

.PHONY: all clean fclean re export $(NAME)

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
	@if [ ! $N = 0 ]; then $(CC) $(FLAGS) -o $(NAME) $(OBJS) $(COMPILE_LIBS); echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[38;5;125m🐼  $(NAME) done\033[0m"; else echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[38;5;125m🦋  nothing to be done done\033[0m"; fi

clean:
	@rm -f $(OBJS)
	@echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[0m\033[38;5;87m$(NAME) removed\033[0m"

norme:
	@norminette $(OBJS:$(OBJ)/%.o=$(SRC)/%.c) $(INCLUDES)

re: fclean all
