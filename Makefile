FT_NM = ft_nm
FT_OTOOL = ft_otool
EXT = Makefile
LIBFT = libft

.PHONY: all clean fclean re norme $(LIBFT)

all: $(FT_NM) $(FT_OTOOL)

$(LIBFT):
	@make -C $(LIBFT)

$(FT_NM): $(LIBFT)
	@make -f $(FT_NM).$(EXT)

$(FT_OTOOL): $(LIBFT)
	@make -f $(FT_OTOOL).$(EXT)

clean:
	@make -C $(LIBFT) clean
	@make -f $(FT_NM).$(EXT) clean
	@make -f $(FT_OTOOL).$(EXT) clean

fclean:
	@make -C $(LIBFT) fclean
	@make -f $(FT_NM).$(EXT) fclean
	@make -f $(FT_OTOOL).$(EXT) fclean

re: fclean all

norme:
	@make -C $(LIBFT) norme
	@make -f $(FT_NM).$(EXT) norme
	@make -f $(FT_OTOOL).$(EXT) norme
