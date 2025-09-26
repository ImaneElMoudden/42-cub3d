CFLAGS = -Wall -Wextra -Werror
SRC = cub3d_bonus.c init_bonus.c \
		parse_bonus.c parse_line_bonus.c parse_line_utils_bonus.c \
		validate_map_bonus.c validate_map_borders_bonus.c \
		ft_split_bonus.c get_next_line_bonus.c \
		line_utils_bonus.c string_utils_bonus.c malloc_bonus.c safe_malloc_bonus.c \
		config_bonus.c init_mlx_bonus.c \
		game_bonus.c raycast_bonus.c draw_bonus.c handle_keys_bonus.c handle_frames_bonus.c \
		movement_bonus.c rotate_bonus.c \
		minimap_bonus.c door_bonus.c \
		color_utils_bonus.c \
		clean_bonus.c \

NAME = cub3D_bonus
OBJ = $(SRC:.c=.o)
MLXFLAGS = -L/usr/include/minilibx-linux -lmlx -lX11 -lXext -lm -g
HDR = cub3d_bonus.h

all: $(NAME)

$(NAME): $(OBJ) $(HDR)
	cc $(CFLAGS) $(OBJ) $(MLXFLAGS) -o $(NAME)

clean:
	rm -rf $(OBJ)

fclean:	clean
	rm -rf $(NAME)

re: fclean all

.PHONY = all clean fclean re