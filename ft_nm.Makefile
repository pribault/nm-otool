NAME =	ft_nm
CC =	clang
FLAGS =	-Wall -Wextra
INC =	include
INCLUDE =	ft_nm.h
INCLUDES =	$(INCLUDE:%.h=$(INC)/%.h)
OBJ =	src/ft_nm_obj
SRC =	src/ft_nm
SRCS =	ft_nm.c flags.c endian.c\
		fat.c mach.c archive.c\
		get.c get_2.c get_3.c\
		get_4.c symtab.c output.c\
		segment.c debug.c symbol.c\
		archive_2.c sort.c reverse.c\
		flags_2.c sort_2.c
OBJS =	$(SRCS:%.c=$(OBJ)/%.o)
LIBFT =	libft
INCLUDE_LIBS =	-I $(LIBFT)/include
COMPILE_LIBS =	-L $(LIBFT) -lft
N =		0
MAX =	$(words $(OBJS))
JOBS =	4
MAKE =	false

.PHONY: all clean fclean re export

.SILENT:

all: $(NAME)
	@if [ $(MAKE) = false ]; then echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[38;5;125m🦋  nothing to be done\033[0m"; fi

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
	@$(eval MAKE=true)

clean:
	@rm -rf $(OBJ)
	@echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[0m\033[38;5;45mobject files removed\033[0m"

fclean: clean
	@rm -f $(NAME)
	@rm -f ft_nm_log nm_log nm_diff
	@echo "\033[0m\033[38;5;124m[∎∎∎∎ $(NAME)] \033[0m\033[38;5;87m$(NAME) removed\033[0m"

norme:
	@norminette $(OBJS:$(OBJ)/%.o=$(SRC)/%.c) $(INCLUDES)

re: fclean all
