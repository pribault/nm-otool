FT_NM = ft_nm
FT_OTOOL = ft_otool
EXT = Makefile
LIBFT = libft
JOBS = 4

.PHONY: all clean fclean re norme $(LIBFT)

all: $(FT_NM) $(FT_OTOOL)

$(LIBFT):
	@make -C $(LIBFT) -j$(JOBS)

$(FT_NM): $(LIBFT)
	@make -f $(FT_NM).$(EXT) -j$(JOBS)

$(FT_OTOOL): $(LIBFT)
	@make -f $(FT_OTOOL).$(EXT) -j$(JOBS)

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
