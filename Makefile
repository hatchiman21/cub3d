LIBFT_DIR = libft
SRC_DIR = src
OBJS_DIR = obj
LIBFT = $(LIBFT_DIR)/libft.a
MLX42_DIR = MLX42/build
MLX = $(MLX42_DIR)/libmlx42.a

SRCS = main
SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))
SRCS := $(addsuffix .c, $(SRCS))
OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJS_DIR)/%.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = cub3d

all: $(LIBFT) $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJS) inc/cub3d.h
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) \
	-L$(LIBFT_DIR) -lft \
	-L$(MLX42_DIR) -lmlx42 -lmlx \
	-lX11 -lXext -lm -I.

$(OBJS_DIR)/%.o: $(SRC_DIR)/%.c inc/cub3d.h | $(OBJS_DIR)
			$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
			mkdir -p $(OBJS_DIR)

bonus: $(LIBFT) $(NAME)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJS_DIR)

fclean:
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(OBJS_DIR)
	$(RM) $(NAME)

re: fclean all

.PHONY: all bonus clean fclean re
