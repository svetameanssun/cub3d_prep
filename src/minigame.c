#include "../include/minigame.h"

char *map[] =
{
    "11111111",
    "10100001",
    "10100001",
    "10100001",
    "10100001",
    "10000001",
    "10000001",
    "10000001",
    "10000001",
    "11111111",
};

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void put_player(data_t *game, int clr)
{
    int min_x;
    int max_x;
    int min_y;
    int max_y;
    int temp;

    min_x = game->player->x - 8;
    max_x = game->player->x + 8;
    min_y = game->player->y - 8;
    max_y = game->player->y + 8;
    temp = min_y;
    if (game->player->x > 0 && game->player->y > 0)
    {
        while(min_x < max_x)
        {
            min_y = temp;
            while(min_y < max_y)
            {
                mlx_put_pixel(game->window, min_x, min_y, clr);
                min_y++;
            }
            min_x++;
        }
    }
    
}

void put_square(data_t *game, int x, int y, int clr)
{
    int min_x = x * 50;  // Multiply by 10 to draw a 10x10 block
    int min_y = y * 50;  // Multiply by 10 to draw a 10x10 block
    int max_x = min_x + 50; // Width of the square (10x10)
    int max_y = min_y + 50; // Height of the square (10x10)
    int clr3 = get_rgba(255, 255, 255, 255);

    // Loop over the range to fill a 10x10 block
    for (int i = min_x; i < max_x; i++)
    {
        for (int j = min_y; j < max_y; j++)
        {
            if (i == min_x || i == max_x - 1 || j == min_y || j == max_y - 1)
            {
                mlx_put_pixel(game->window, i, j, clr3); // Draw white border
            }
            else
            {
                mlx_put_pixel(game->window, i, j, clr);  // Set pixel color

            }
        }
    }
}

void draw_map_2D(data_t *game)
{
    game->clr_floor = get_rgba(235, 64, 52, 255);  // Color for '1'
    game->clr_walls = get_rgba(0, 0, 0, 255);    // Color for '0'

    int i = 0;
    int j = 0;

    while (map[i] != NULL)
    {
        j = 0;
        while (map[i][j] != '\0')
        {
            if (map[i][j] == '1')  // If '1', draw square with clr
            {
                game->clr_current = game->clr_floor;
                put_square(game, j, i, game->clr_floor);  // Corrected x, y coordinates
            }
            else  // If '0', draw square with clr2
            {
                game->clr_current = game->clr_floor;
                put_square(game, j, i, game->clr_walls);  // Corrected x, y coordinates
            }
            j++;
        }
        i++;
    }
}

void init_player(data_t *game)
{
    game->player->clr = get_rgba(79, 235, 52, 255);
    game->player->x = 50;
    game->player->y = 50;
    game->player->ang = 0;
    game->player->delta_x = cos(game->player->ang) *5;
    game->player->delta_y = sin(game->player->ang) *5;
}

void button_change_view(void *param)
{
    data_t *game = (data_t*)param;
    if(game->player->ang < 0)
        game->player->ang = 360 + game->player->ang;
    if(game->player->ang > 360)
        game->player->ang = game->player->ang - 360;
    if (mlx_is_key_down(game->mlx, MLX_KEY_A))
    {
        game->player->ang +=0.1;
        game->player->delta_x = cos(game->player->ang) *5;
        game->player->delta_y = sin(game->player->ang) *5;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_D))
    {
        game->player->ang -=0.1;
        game->player->delta_x = cos(game->player->ang) *5;
        game->player->delta_y = sin(game->player->ang) *5;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_W))
    {
        game->player->x -= game->player->delta_x;
        game->player->y -= game->player->delta_y;
    }
    if (mlx_is_key_down(game->mlx, MLX_KEY_S))
    {
        game->player->x += game->player->delta_x;
        game->player->y += game->player->delta_y;
    }
    
}

void button_move(void *param)
{
    data_t *game = (data_t*)param;
    put_player(game, game->clr_current);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
        game->player->y -= 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player->y += 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->x -= 1;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->x += 1;
   put_player(game, game->player->clr);
}


int main()
{
    data_t game;
    player_t player;
    game.player = &player;
    game.mlx = mlx_init(WIDTH, HEIGHT, "minigame", 0);
     game.window = mlx_new_image(game.mlx, WIDTH, HEIGHT);
    if (!game.window)
    {
        fprintf(stderr, "Failed to create image\n");
        return 1; // Exit if window creation fails
    }      

    mlx_image_to_window(game.mlx, game.window, 0, 0);
    draw_map_2D(&game);
    init_player(&game);
    put_player(&game, game.player->clr);
    //mlx_set_setting(MLX_MAXIMIZED, true);
    mlx_loop_hook(game.mlx, button_change_view, (void*)&game);
    mlx_loop_hook(game.mlx, button_move, (void*)&game);
    mlx_loop(game.mlx);

}