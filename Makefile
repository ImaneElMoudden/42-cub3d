CFLAGS = -Wall -Wextra -Werror

SRC = mandatory/parsing/clean.c mandatory/parsing/color_utils.c mandatory/parsing/ft_split.c mandatory/parsing/get_next_line.c \
		mandatory/parsing/init.c mandatory/parsing/line_utils.c mandatory/parsing/malloc.c  mandatory/parsing/parse_line_utils.c \
		mandatory/parsing/parse_line.c mandatory/parsing/parse.c mandatory/parsing/safe_malloc.c mandatory/parsing/string_utils.c \
		mandatory/parsing/validate_map_borders.c mandatory/parsing/validate_map.c \
		mandatory/engine/cub3d.c  mandatory/engine/config.c mandatory/engine/init_mlx.c mandatory/engine/handle_frames.c \
		mandatory/engine/hooks_handlers.c mandatory/engine/actions.c mandatory/engine/raycasting.c mandatory/engine/draw.c

SRC_BONUS = bonus/cub3d_bonus.c bonus/init_bonus.c \
		bonus/parse_bonus.c bonus/parse_line_bonus.c bonus/parse_line_utils_bonus.c \
		bonus/validate_map_bonus.c bonus/validate_map_borders_bonus.c \
		bonus/ft_split_bonus.c bonus/get_next_line_bonus.c \
		bonus/line_utils_bonus.c bonus/string_utils_bonus.c bonus/malloc_bonus.c bonus/safe_malloc_bonus.c \
		bonus/config_bonus.c bonus/init_mlx_bonus.c \
		bonus/game_bonus.c bonus/raycast_bonus.c bonus/draw_bonus.c bonus/handle_keys_bonus.c bonus/handle_frames_bonus.c \
		bonus/movement_bonus.c \
		bonus/minimap_bonus.c bonus/minimap_utils_bonus.c bonus/door_bonus.c \
		bonus/color_utils_bonus.c \
		bonus/clean_bonus.c

NAME = cub3D
BONUS = cub3D_bonus
OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)
HDR = mandatory/cub3d.h
HDR_BONUS = bonus/cub3d_bonus.h
MLXFLAGS = -L/usr/include/minilibx-linux -lmlx -lX11 -lXext -lm

all: $(NAME)

bonus: $(BONUS)

$(NAME): $(OBJ) $(HDR)
	cc $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

$(BONUS): $(OBJ_BONUS) $(HDR_BONUS)
	cc $(CFLAGS) $(OBJ_BONUS) $(MLXFLAGS) -o $(BONUS)

clean:
	rm -f $(OBJ) $(OBJ_BONUS)

fclean:	clean
	rm -f $(NAME) $(BONUS)

re: fclean all

.PHONY: all clean fclean re bonus
