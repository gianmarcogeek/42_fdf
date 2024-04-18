#ANSI text style
BOLD = \e[1m
RED = \e[91m
GREEN = \e[92m
RESET = \e[0m

#Compilation variables
NAME = fdf
CC = gcc
CFLAGS = -g
INCLUDE = -I/usr/include -Imlx_linux 
LINK = -lXext -lX11 -lm -lz

#Paths
SRC_DIR = ./src
SRCS = $(SRC_DIR)/*.c

LIBFT_DIR = ./lib/libft
LIBFT_A = $(LIBFT_DIR)/libft.a

FT_PRINTF_DIR = ./lib/ft_printf
FT_PRINTF_A = $(FT_PRINTF_DIR)/libftprintf.a

MLX_DIR = ./lib/minilibx-linux
MLX_A = $(MLX_DIR)/libmlx_Linux.a

$(NAME) : $(LIBFT_A) $(FT_PRINTF_A)
	@echo "Compiling $(NAME)"
	@$(CC) $(CFLAGS) $(SRCS) $(LIBFT_A) $(FT_PRINTF_A) $(MLX_A) $(LINK) -o $(NAME)
	@echo "$(BOLD)$(GREEN)$(NAME) compiled successfully!$(RESET)"

$(LIBFT_A) :
	@echo "Compiling libft$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR)

$(FT_PRINTF_A) :
	@echo "Compiling ft_printf$(RESET)"
	@$(MAKE) -s -C $(FT_PRINTF_DIR)

all : $(NAME)

clean :
	@echo "$(BOLD)Cleaning...$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR) clean
	@$(MAKE) -s -C $(FT_PRINTF_DIR) clean

fclean : clean
	@echo "$(BOLD)$(RED)Full cleaning...$(RESET)"
	@$(MAKE) -s -C $(LIBFT_DIR) fclean
	@$(MAKE) -s -C $(FT_PRINTF_DIR) fclean
	@rm -f $(NAME)

re : fclean all

.PHONY : all clean fclean re