NAME = cub3D

CC = clang
CFLAGS = -Wall -Werror -Wextra $(COPT)
CPPFLAGS = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
COPT ?= -O2

SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/parse/errors.c \
	$(SRC_DIR)/parse/errors2.c \
	$(SRC_DIR)/parse/errors3.c \
	$(SRC_DIR)/parse/free.c \
	$(SRC_DIR)/parse/headers.c \
	$(SRC_DIR)/parse/map.c \
	$(SRC_DIR)/parse/parse.c \
	$(SRC_DIR)/parse/utils.c \
	$(SRC_DIR)/color.c \
	$(SRC_DIR)/doublebuff.c \
	$(SRC_DIR)/errors.c \
	$(SRC_DIR)/events.c \
	$(SRC_DIR)/init.c \
	$(SRC_DIR)/main.c
OBJ = $(SRC:.c=.o)

INC_DIR = ./inc

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./libs/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

LDFLAGS = -L$(MLX_DIR) -L$(LIBFT_DIR)
LDLIBS = -lm -lmlx -lXext -lX11

all: $(NAME)

$(NAME): $(MLX) $(LIBFT) $(OBJ)
	$(CC) $(OBJ) $(LIBFT) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	 $(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

clean:
	$(RM) $(OBJ)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)

fclean: clean
	$(RM) $(OBJ) $(NAME)

re: fclean all

debug: CFLAGS += -g3 -fno-omit-frame-pointer
debug: COPT = -Og
debug: all

dev: CFLAGS += -g3 -fno-omit-frame-pointer -fsanitize=address,undefined,leak
dev: COPT = -Og
dev: all

.PHONY: all fclean clean re debug dev
