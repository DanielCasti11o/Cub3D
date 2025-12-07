NAME = cub3D

CC ?= cc
CFLAGS = -Wall -Werror -Wextra $(COPT)
CPPFLAGS = -I$(INC_DIR) -I$(MLX_DIR) -I$(LIBFT_DIR)
COPT ?= -O2

SRC_DIR = ./src
SRC = \
	$(SRC_DIR)/core/init.c \
	$(SRC_DIR)/core/loop.c \
	$(SRC_DIR)/events/hooks.c \
	$(SRC_DIR)/events/movement.c \
	$(SRC_DIR)/events/mouse_hooks.c \
	$(SRC_DIR)/parse/errors.c \
	$(SRC_DIR)/parse/errors2.c \
	$(SRC_DIR)/parse/errors3.c \
	$(SRC_DIR)/parse/headers.c \
	$(SRC_DIR)/parse/map.c \
	$(SRC_DIR)/parse/parse.c \
	$(SRC_DIR)/parse/utils.c \
	$(SRC_DIR)/rendering/animated.c \
	$(SRC_DIR)/rendering/doublebuff.c \
	$(SRC_DIR)/rendering/minimap.c \
	$(SRC_DIR)/rendering/ray.c \
	$(SRC_DIR)/rendering/wall.c \
	$(SRC_DIR)/rendering/door_dist.c \
	$(SRC_DIR)/rendering/door.c \
	$(SRC_DIR)/rendering/utils.c \
	$(SRC_DIR)/utils/color.c \
	$(SRC_DIR)/utils/errors.c \
	$(SRC_DIR)/utils/free.c \
	$(SRC_DIR)/utils/math.c \
	$(SRC_DIR)/rendering/big_minmap.c \
	$(SRC_DIR)/main.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC:.c=_bonus.o)

INC_DIR = ./inc

LIBFT_DIR = ./libs/libft
LIBFT = $(LIBFT_DIR)/libft.a

MLX_DIR = ./libs/minilibx-linux
MLX = $(MLX_DIR)/libmlx.a

LDFLAGS = -L$(MLX_DIR) -L$(LIBFT_DIR)
LDLIBS = -lm -lmlx -lXext -lX11 -lXfixes

NORMAL_FLAG = .all_build
BONUS_FLAG = .bonus_build

all: $(NORMAL_FLAG)

$(NORMAL_FLAG): $(MLX) $(LIBFT) $(OBJ)
	$(RM) $(BONUS_FLAG)
	$(CC) $(OBJ) $(LIBFT) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	touch $@

%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

bonus: $(BONUS_FLAG)

$(BONUS_FLAG): $(MLX) $(LIBFT) $(OBJ_BONUS)
	$(RM) $(NORMAL_FLAG)
	$(CC) $(OBJ_BONUS) $(LIBFT) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) -o $(NAME)
	touch $@

%_bonus.o: CFLAGS += -DBONUS=1
%_bonus.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_DIR)

$(MLX):
	make -C $(MLX_DIR)

norm:
	norminette $(INC_DIR) $(SRC_DIR) $(LIBFT_DIR)

clean:
	$(RM) $(OBJ)
	make fclean -C $(LIBFT_DIR)
	make clean -C $(MLX_DIR)
	$(RM) $(NORMAL_FLAG) $(BONUS_FLAG)

fclean: clean
	$(RM) $(OBJ) $(NAME)

re: fclean all

debug: CFLAGS += -g3 -fno-omit-frame-pointer
debug: COPT = -Og
debug: all

dev: CFLAGS += -g3 -fno-omit-frame-pointer -fsanitize=address,undefined,leak
dev: COPT = -Og
dev: all

.PHONY: all bonus fclean clean re debug dev
