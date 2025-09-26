#include "cub3d_bonus.h"

void get_minimap_limits(t_game *game, t_minimap *minimap, t_player *player)
{
    minimap->start_x = player->pos_x - NB_TILES / 2.0;
    minimap->end_x = player->pos_x + NB_TILES / 2.0;
    minimap->start_y = player->pos_y - NB_TILES / 2.0;
    minimap->end_y = player->pos_y + NB_TILES / 2.0;
    if (minimap->start_x < 0)
        minimap->start_x = 0;
    if (minimap->end_x >= game->map.map_width)
        minimap->start_x = game->map.map_width - NB_TILES;
    if (minimap->start_y < 0)
        minimap->start_y = 0;
    if (minimap->end_y >= game->map.map_height)
        minimap->start_y = game->map.map_height - NB_TILES;
    minimap->end_x = minimap->start_x + NB_TILES;
    minimap->end_y = minimap->start_y + NB_TILES;
    minimap->player_pos_x = player->pos_x - minimap->start_x;
    minimap->player_pos_y = player->pos_y - minimap->start_y;
}

unsigned int which_color(t_game *game, int x, int y)
{
    int map_x;
    int map_y;

    map_x = (game->minimap.start_x + (double)x / TEX_SIZE);
    map_y = (game->minimap.start_y + (double)y / TEX_SIZE);
    
    if (game->map.map[map_y][map_x] == '0')
        return (0x000000);
    if (game->map.map[map_y][map_x] == '1')
        return (0x808080);
    if (game->map.map[map_y][map_x] == 'd')
        return (0x8B4513);
    if (game->map.map[map_y][map_x] == 'D')
        return (0xFFFF00);
    return (0);
}

void draw_player_dot(t_game *game, t_minimap *minimap, int color)
{
    int x;
    int y;
    int minimap_x;
    int minimap_y;
    int pixel_x;
    int pixel_y;

    y = -VIEW_RADIUS;
    minimap_x = minimap->player_pos_x * TEX_SIZE;
    minimap_y = minimap->player_pos_y * TEX_SIZE;
    while (y < VIEW_RADIUS)
    {
        x = -VIEW_RADIUS;
        while (x < VIEW_RADIUS)
        {
            pixel_x = minimap_x + x + OFFSET;
            pixel_y = minimap_y + y + OFFSET;
            if (sqrt(x * x + y * y) < VIEW_RADIUS)
                put_pixel(&game->mlx.img, pixel_x, pixel_y, color);
            x++;
        }
        y++;
    }
}

void display_minimap()
{
    t_game *game = game_data();
    t_player *player;
    t_minimap *minimap;
    t_img *img;
    int x;
    int y;
    unsigned int color;

    y = -1;
    player = &game->player;
    minimap = &game->minimap;
    img = &game->mlx.img;
    get_minimap_limits(game, minimap, player);
    while (++y < MINIMAP_SIZE)
    {
        x = -1;
        while (++x < MINIMAP_SIZE)
        {
            color = which_color(game, x , y);
            put_pixel(&game->mlx.img, x + OFFSET, y + OFFSET, color);
            x++;
        }
        // y++;
    }
    draw_player_dot(game, minimap, 0xFF0000);
}
