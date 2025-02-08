#ifndef MINIGAME_H
#define MINIGAME_H

#define HEIGHT 650
#define WIDTH 1270

#include <math.h>
#include <stdio.h>
#include "../MLX42/include/MLX42/MLX42.h"

typedef struct player_s
{
    int x;
    int y;
    int clr;
    double ang;
    double delta_x;
    double delta_y;
}   player_t;

typedef struct game_data_s
{
    player_t *player;
    mlx_t *mlx;
    mlx_image_t *window;
    int clr_floor;
    int clr_walls;
    int clr_current;
}   data_t;

#endif