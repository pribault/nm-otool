NAME = ft_nm
CC = clang
FLAGS = -Wall -Wextra -Werror
INC = include
INCLUDE = ft_nm.h
INCLUDES = $(INCLUDE:%.h=$(INC)/%.h)
OBJ = src/ft_nm_obj
SRC = src/ft_nm
SRCS =	ft_nm.c
OBJS = $(SRCS:%.c=$(OBJ)/%.o)
LIBFT = libft
INCLUDE_LIBS = -I $(LIBFT)/include
COMPILE_LIBS = -L $(LIBFT) -lft

.PHONY: all clean fclean re export

all: $(NAME)

$(OBJ):
	@mkdir $@

$(LIBFT)/libft.a:

$(OBJ)%.o: $(SRC)%.c $(INCLUDES) $(LIBFT)/libft.a | $(OBJ)
	@echo "\033[38;5;207m🍇  compiling $@\033[0m"
	@$(CC) $(FLAGS) -I $(INC) $(INCLUDE_LIBS) -o $@ -c $<
	@echo "\033[1A\033[K\033[38;5;207m🍇  $@ done\033[0m"

$(NAME): $(OBJS)
	@echo "\033[38;5;125m🐼  compiling $(NAME)\033[0m"
	@$(CC) $(FLAGS) -o $(NAME) $(OBJS) $(COMPILE_LIBS)
	@echo "\033[1A\033[K\033[38;5;125m🐼  $(NAME) done\033[0m"

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

norme:
	@norminette $(OBJS:%.o=%.c) $(INCLUDES)

re: fclean all
