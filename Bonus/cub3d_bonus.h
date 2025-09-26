#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

#define _XOPEN_SOURCE 500

# include "minilibx-linux/mlx.h"
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/types.h>
# include <unistd.h>
// remove stdio
# include <stdio.h>
# include <string.h>

# define WIDTH 800
# define HEIGHT 600
// # define WIDTH 1920
// # define HEIGHT 1080
# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif
# define FOV 60
# define FOV_RAD (FOV * M_PI / 180.0)
# define PLANE_LEN (tan(FOV_RAD / 2))

# define MARGIN 0.2
# define BASE_MOVE_SPEED 3.0f // 3 tiles per second
# define BASE_ROT_SPEED 2.0f  // 2 radians per second

// minimap
# define TEX_SIZE 15
# define OFFSET 20
# define VIEW_RADIUS 4
# define MINIMAP_SIZE (WIDTH / 5)
# define NB_TILES ((double)MINIMAP_SIZE / TEX_SIZE)

// mouse
# define MOUSE_SENS 0.003f // radians per pixel

// open door
# define DOOR_DIST 1.2

// gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

typedef struct s_player
{
	float			pos_x;
	float			pos_y;
	float			dir_x;
	float			dir_y;
	float			plane_x;
	float			plane_y;
}					t_player;

typedef struct s_ray
{
	float			camera_x;
	float			raydir_x;
	float			raydir_y;
	int				map_x;
	int				map_y;
	float			delta_dist_x;
	float			delta_dist_y;
	int				step_x;
	int				step_y;
	float			sidedist_x;
	float			sidedist_y;
	int				side;
	float			perpwall_dist;
	int				line_height;
	int				draw_start;
	int				draw_end;
}					t_ray;

typedef struct s_img
{
	void *mlx_img; // mlx image pointer
	char *addr;    // image data (raw pixel buffer)
	int bpp;       // bits per pixel
	int line_len;  // size of one row in bytes
	int endian;    // endianess
	int width;     // width of the image (screen WIDTH)
	int height;    // height of the image (screen HEIGHT)
}					t_img;

typedef enum e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	CLOSED_DOOR,
	// POTION_1, // animation
	// POTION_2,
	// POTION_3,
	TEX_SUM
}					t_dir;

typedef enum e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_E,
	KEY_SUM
}					t_key;

typedef struct s_sprite
{
	float			x;
	float			y;
	int				tex_id;
}					t_sprite;

typedef struct s_minimap
{
	double			start_x;
	double			end_x;
	double			start_y;
	double			end_y;
	double          player_pos_x;
	double          player_pos_y;
	int				minimap_size;
	int				unit_size;
}					t_minimap;

typedef struct s_input
{
	char			*no_path;
	char			*so_path;
	char			*we_path;
	char			*ea_path;
	int				floor_color; // type
	int				ceiling_color;
	int				input_fd;
	char			player_dir;
}					t_input;

typedef struct s_malloc
{
	void			*ptr;
	size_t			size;
	struct s_malloc	*next;
}					t_malloc;

typedef struct s_map
{
	char			**map;
	int				map_width;
	int				map_height;
}					t_map;

typedef struct s_mlx
{
	void			*mlx;
	void			*mlx_win;
	t_img			tex[TEX_SUM];
	t_img			img;
	int				keys[KEY_SUM];
}					t_mlx;

typedef struct s_mouse
{
	int				x;
	int				y;
}					t_mouse;

typedef struct s_time
{
	double			delta_time;
	double			last_time;
	double			now;
	double			elapsed;
	double			target;
}					t_time;

typedef struct s_draw
{
	int				color;
	int				tex_x;
	int				tex_y;
	float			wall_x;
	float			step;
	float			tex_pos;
}					t_draw;

typedef struct s_game
{
	t_input			input;
	struct s_map	map;
	struct s_player	player;
	struct s_ray	ray;
	struct s_draw	draw;
	struct s_mlx	mlx;
	struct s_time	time;
	struct s_mouse	mouse;
	t_minimap		minimap;
	t_malloc		*mallc;
}					t_game;

// ---------- Prototypes  ---------- //

// init
void				*ft_memset(void *s, int c, size_t n);
void				init(void);
t_game				*game_data(void);

// ---------- Parse ---------- //
// parse
int					check_input(int ac, char **av);
int					check_file(char *file);

// parse_line
int					parse_line(char *line, int fd);

// parse_line_utils
int					invalid_file_content(void);
int					ft_atoi(const char *str);
int					count_array(char **arr);
char				**append_arr(char **arr, char *line, int l);

// validate_map
int					validate_map(void);

// validate_map_borders
int					check_map_boundaries(void);
int					finalize_map(void);

// ---------- Game ---------- //
// config
void				config_game(void);

// init_mlx
int					init_mlx(void);

// game
int					game_loop(void *p);

// handle_frames
double				get_time_in_seconds(void);
void				handle_frames(void);

// raycast
void				raycast(void);

// draw
void				draw_background(t_img *img, int ceiling, int floor);
void				draw(int x);

// handle_keys
int					handle_key(int key, void *p);
int					handle_key_release(int key, void *p);
int					mouse_movement(int x, int y, void *p);

// movement
void				move_up(void);
void				move_down(void);
void				move_left(void);
void				move_right(void);

// rotate
void				rotate(float angle);
void				rotate_left(void);
void				rotate_right(void);

// door
void					handle_door(t_map *map);

// minimap
void				display_minimap(void);

// color_utils
void				put_pixel(t_img *img, int x, int y, int color);
int					create_rgb(int i, int j, int k);

// ---------- Utils ---------- //
// ft_split
char				**ft_split(char const *s, char c);

// get_next_line
char				*get_next_line(int fd);

// malloc
void				*safe_malloc(size_t size);
void				safe_free(void);

// safe_malloc
char				*safe_strjoin(char const *s1, char const *s2);
char				*safe_strdup(const char *s);
char				*safe_substr(char const *s, unsigned int start, size_t len);

// string_utils
int					ft_strlen(const char *s);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
size_t				ft_strlcpy(char *dst, const char *src, size_t size);
char				*ft_strchr(const char *s, int c);

// line_utils
int					ft_isspace(char c);
int					is_empty_line(char *line);
int					is_numeric(char *str);
int					write_error(char *str);

// clean
int					clean(void *p);

#endif