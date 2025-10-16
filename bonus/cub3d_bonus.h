/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: klamachi <klamachi@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/26 09:39:27 by ielmoudd          #+#    #+#             */
/*   Updated: 2025/10/16 09:41:14 by klamachi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <minilibx-linux/mlx.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>

# define WIDTH 800
# define HEIGHT 600
// # define WIDTH 1920
// # define HEIGHT 1080
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define FOV 60

// movement
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0

// minimap
# define TEX_SIZE 15
# define OFFSET 20
# define PLAYER_SIZE 3

// mouse
# define MOUSE_SENS 0.003

// door
# define DOOR_DIST 1.2

// gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

// typedef
typedef struct s_player		t_player;
typedef struct s_ray		t_ray;
typedef struct s_img		t_img;
typedef enum e_dir			t_dir;
typedef enum e_key			t_key;
typedef struct s_sprite		t_sprite;
typedef struct s_minimap	t_minimap;
typedef struct s_input		t_input;
typedef struct s_malloc		t_malloc;
typedef struct s_map		t_map;
typedef struct s_mlx		t_mlx;
typedef struct s_mouse		t_mouse;
typedef struct s_time		t_time;
typedef struct s_draw		t_draw;
typedef struct s_game		t_game;

// structs
struct						s_player
{
	double					pos_x;
	double					pos_y;
	double					dir_x;
	double					dir_y;
	double					plane_x;
	double					plane_y;
};

struct						s_ray
{
	double					camera_x;
	double					raydir_x;
	double					raydir_y;
	int						map_x;
	int						map_y;
	double					delta_dist_x;
	double					delta_dist_y;
	int						step_x;
	int						step_y;
	double					sidedist_x;
	double					sidedist_y;
	int						side;
	double					perpwall_dist;
	int						line_height;
	int						draw_start;
	int						draw_end;
};

struct						s_img
{
	void					*mlx_img;
	char					*addr;
	int						bpp;
	int						line_len;
	int						endian;
	int						width;
	int						height;
};

enum						e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	CLOSED_DOOR,
	TEX_SUM
};

enum						e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_E,
	KEY_SUM
};

struct						s_sprite
{
	double					x;
	double					y;
	int						tex_id;
};

struct						s_minimap
{
	double					start_x;
	double					end_x;
	double					start_y;
	double					end_y;
	double					player_pos_x;
	double					player_pos_y;
	int						minimap_size;
	int						nb_tiles;
	int						x;
	int						y;
	unsigned int			color;
	int						player_pixel_x;
	int						player_pixel_y;
};

struct						s_input
{
	char					*no_path;
	char					*so_path;
	char					*we_path;
	char					*ea_path;
	int						floor_color;
	int						ceiling_color;
	int						input_fd;
	char					player_dir;
};

struct						s_malloc
{
	void					*ptr;
	size_t					size;
	struct s_malloc			*next;
};

struct						s_map
{
	char					**map;
	int						map_width;
	int						map_height;
};

struct						s_mlx
{
	void					*mlx;
	void					*mlx_win;
	t_img					tex[TEX_SUM];
	t_img					img;
	int						keys[KEY_SUM];
};

struct						s_mouse
{
	int						x;
	int						y;
};

struct						s_time
{
	double					delta_time;
	double					last_time;
	double					now;
	double					elapsed;
	double					target;
};

struct						s_draw
{
	int						color;
	int						tex_x;
	int						tex_y;
	double					wall_x;
	double					step;
	double					tex_pos;
};

struct						s_game
{
	t_input					input;
	t_map					map;
	t_player				player;
	t_ray					ray;
	t_draw					draw;
	t_mlx					mlx;
	t_time					time;
	t_mouse					mouse;
	t_minimap				minimap;
	t_malloc				*mallc;
};

// ---------- Prototypes  ---------- //

// init
void						*ft_memset(void *s, int c, size_t n);
void						init(void);
t_game						*game_data(void);

// ---------- Parse ---------- //
// parse
int							check_input(int ac, char **av);
int							check_file(char *file);

// parse_line
int							parse_line(char *line, int fd);

// parse_line_utils
int							invalid_file_content(void);
int							convert_color(char *str);
int							count_array(char **arr);
char						**append_arr(char **arr, char *line, int l);

// validate_map
int							validate_map(void);

// validate_map_borders
int							check_map_boundaries(void);
int							finalize_map(void);

// ---------- Game ---------- //
// config
void						config_game(void);

// init_mlx
int							init_mlx(void);

// game
int							game_loop(void *p);

// handle_frames
double						get_time_in_seconds(void);
void						handle_frames(void);

// raycast
void						raycast(void);

// draw
void						draw(int x);

// handle_keys
int							handle_key(int key, void *p);
int							handle_key_release(int key, void *p);
int							mouse_movement(int x, int y, void *p);

// movement
void						move(double dir1, double dir2);
void						rotate(double angle);

// door
void						handle_door(t_map *map);

// minimap
void						display_minimap(void);
void						draw_player_dir(t_game *game, unsigned int color);

// color_utils
void						put_pixel(t_img *img, int x, int y, int color);
int							create_rgb(int i, int j, int k);

// ---------- Utils ---------- //
// ft_split
char						**ft_split(char const *s, char c);

// get_next_line
char						*get_next_line(int fd);

// malloc
void						*safe_malloc(size_t size);
void						safe_free(void);

// safe_malloc
char						*safe_strjoin(char const *s1, char const *s2);
char						*safe_strdup(const char *s);
char						*safe_substr(char const *s, unsigned int start,
								size_t len);

// string_utils
int							ft_strlen(const char *s);
int							ft_strncmp(const char *s1, const char *s2,
								size_t n);
size_t						ft_strlcpy(char *dst, const char *src, size_t size);
char						*ft_strchr(const char *s, int c);

// line_utils
int							ft_isspace(char c);
int							is_empty_line(char *line);
int							write_error(char *str);
int							exit_error(char *str);

// clean
int							clean(void *p);

#endif