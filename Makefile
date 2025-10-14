NAME = cub3D
CC = cc
CFLAGS = -Wall -Werror -Wextra -g3 -lm -Lmlx -lmlx -lXext -lX11 -L$(MLX_A)
SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/main.c \
	$(SRC_DIR)/init.c
INC_DIR = ./inc
LIBFT_DIR = ./libs/libft_bonus
MLX_DIR = ./libs/minilibx-linux
MLX_A = $(MLX_DIR)/libmlx.a
INCLUDE = \
	-I$(INC_DIR) \
	-I$(MLX_DIR) \
	-L$(MLX_DIR) \
	-I$(LIBFT_DIR)
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

fclean:
	$(RM) $(OBJ) $(NAME)
	make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all fclean clean
