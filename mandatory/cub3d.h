/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ielmoudd <ielmoudd@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 13:55:59 by klamachi          #+#    #+#             */
/*   Updated: 2025/10/12 17:54:15 by ielmoudd         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

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
# define FOV 60.0

// movement
# define MOVE_SPEED 3.0
# define ROT_SPEED 2.0

// gnl
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 40
# endif

# if BUFFER_SIZE < 0
#  undef BUFFER_SIZE
#  define BUFFER_SIZE 0
# endif

// typedef
typedef struct s_player	t_player;
typedef struct s_ray	t_ray;
typedef struct s_img	t_img;
typedef enum e_dir		t_dir;
typedef enum e_key		t_key;
typedef struct s_input	t_input;
typedef struct s_malloc	t_malloc;
typedef struct s_map	t_map;
typedef struct s_mlx	t_mlx;
typedef struct s_time	t_time;
typedef struct s_draw	t_draw;
typedef struct s_game	t_game;

// structs
struct					s_player
{
	double				pos_x;
	double				pos_y;
	double				dir_x;
	double				dir_y;
	double				plane_x;
	double				plane_y;
};

struct					s_ray
{
	double				camera_x;
	double				raydir_x;
	double				raydir_y;
	int					map_x;
	int					map_y;
	double				delta_dist_x;
	double				delta_dist_y;
	int					step_x;
	int					step_y;
	double				sidedist_x;
	double				sidedist_y;
	int					side;
	double				perpwall_dist;
	int					line_height;
	int					draw_start;
	int					draw_end;
};

struct					s_img
{
	void				*mlx_img;
	char				*addr;
	int					bpp;
	int					line_len;
	int					endian;
	int					width;
	int					height;
};

enum					e_dir
{
	NORTH,
	SOUTH,
	EAST,
	WEST,
	TEX_SUM
};

enum					e_key
{
	KEY_W,
	KEY_A,
	KEY_S,
	KEY_D,
	KEY_LEFT,
	KEY_RIGHT,
	KEY_SUM
};

struct					s_input
{
	char				*no_path;
	char				*so_path;
	char				*we_path;
	char				*ea_path;
	int					floor_color;
	int					ceiling_color;
	int					input_fd;
	char				player_dir;
};

struct					s_malloc
{
	void				*ptr;
	size_t				size;
	struct s_malloc		*next;
};

struct					s_map
{
	char				**map;
	int					map_width;
	int					map_height;
};

struct					s_mlx
{
	void				*mlx;
	void				*mlx_win;
	t_img				tex[TEX_SUM];
	t_img				img;
	int					keys[KEY_SUM];
};

struct					s_time
{
	double				delta_time;
	double				last_time;
	double				now;
	double				elapsed;
	double				target;
};

struct					s_draw
{
	int					color;
	int					tex_x;
	int					tex_y;
	double				wall_x;
	double				step;
	double				tex_pos;
};

struct					s_game
{
	t_input				input;
	t_map				map;
	t_player			player;
	t_ray				ray;
	t_draw				draw;
	t_mlx				mlx;
	t_time				time;
	t_malloc			*mallc;
};

// ----------- PARSING --------------
// clean.c
int						clean(void *p);
// color_utils.c
void					put_pixel(t_img *img, int x, int y, int color);
int						create_rgb(int i, int j, int k);
// ft_split.c
char					**ft_split(char const *s, char c);
// gnl
char					*get_next_line(int fd);
// init.c
t_game					*game_data(void);
void					init(void);
void					*ft_memset(void *s, int c, size_t n);
// line_utils.c
int						ft_isspace(char c);
int						is_empty_line(char *line);
int						write_error(char *str);
int						exit_error(char *str);
// malloc.c
void					*safe_malloc(size_t size);
void					safe_free(void);
// parse_line_utils.c
int						invalid_file_content(void);
int						convert_color(char *str);
int						count_array(char **arr);
char					**append_arr(char **arr, char *line, int l);
// parse_line.c
int						parse_line(char *line, int fd);
// parse.c
int						check_file(char *file);
int						check_input(int ac, char **av);
// safe_malloc.c
char					*safe_strjoin(char const *s1, char const *s2);
char					*safe_strdup(const char *s);
char					*safe_substr(char const *s, unsigned int start,
							size_t len);
// string_ulils.c
int						ft_strlen(const char *s);
int						ft_strncmp(const char *s1, const char *s2, size_t n);
size_t					ft_strlcpy(char *dst, const char *src, size_t size);
char					*ft_strchr(const char *s, int c);
// validate_map_border.c
int						check_map_boundaries(void);
int						finalize_map(void);
// validate_map.c
int						validate_map(void);

// ---------------- ENGINE ------------
// config.c
void					config_game(void);
// init_mlx.c
void					init_mlx_var(void);
void					exit_with_error(char *msg);
// handle_frames.c
double					get_time_in_seconds(void);
void					frames_handler(void);
// hooks_handlers.c
int						press_handler(int key_code, void *param);
int						release_handler(int key_code, void *param);
int						ft_render(void *param);
// actions.c
void					move(double dir_x, double dir_y);
void					rotate(int dir_rot);
void					actions(void);
// raycasting.c
void					raycasting(void);
// draw
void					fr_draw(t_ray *ray, int x);

#endif