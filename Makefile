NAME = cub3D

CC = cc
CFLAGS = -Wall -Werror -Wextra $(INCLUDES) -g3

SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c

INC_DIR = ./inc
INCLUDE = \
	-I$(INC_DIR) \
	-I$(MLX_DIR) \
	-I$(LIBFT_DIR)
INCLUDES = -L$(MLX_DIR) -lm -Lmlx -lmlx -lXext -lX11

LIBFT_DIR = ./libs/libft_bonus

MLX_DIR = ./libs/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ) $(MLX) $(LIBFT)
	$(CC) $(OBJ) $(CFLAGS) $(INCLUDE) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	 $(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJ)
	make clean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean:
	$(RM) $(OBJ) $(NAME)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

re: fclean all

.PHONY: all fclean clean re
