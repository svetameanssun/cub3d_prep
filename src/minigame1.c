#include "../include/minigame.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void init_player(data_t *game)
{

    game->player->x = 300;
    game->player->y = 300;
    game->player->clr = get_rgba(189, 0, 0, 225);
    game->player->ang = 0;
}

void draw_window(data_t *game)
{
    int y;
    int x;

    y = 0;
    x = 0;
    game->clr_floor = get_rgba(52, 235, 58, 255);
    game->mlx = mlx_init(WIDTH, HEIGHT, "minigame", 0);
    game->window = mlx_new_image(game->mlx, WIDTH, HEIGHT);
    mlx_image_to_window(game->mlx, game->window, 0, 0);
    while(x < WIDTH)
    {
        y = 0;
        while(y < HEIGHT)
        {
            mlx_put_pixel(game->window, x, y, game->clr_floor);
            y++;
        }
        x++;
    }

}

void put_square(data_t *game, int clr)
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

void button(void *param)
{
    data_t *game = (data_t*)param;
    put_square(game, game->clr_floor);
	if (mlx_is_key_down(game->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(game->mlx);
	if (mlx_is_key_down(game->mlx, MLX_KEY_UP))
        game->player->y -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_DOWN))
		game->player->y += 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_LEFT))
		game->player->x -= 5;
	if (mlx_is_key_down(game->mlx, MLX_KEY_RIGHT))
		game->player->x += 5;
   put_square(game, game->player->clr);
}

int main()
{
    data_t game;
    player_t player;
    game.player = &player;
    printf("1\n");
    init_player(&game);
    printf("2\n");
    draw_window(&game);
    printf("3\n");
    //mlx_set_setting(MLX_MAXIMIZED, true);
    
    mlx_loop_hook(game.mlx, button, (void*)&game);
    mlx_loop(game.mlx);

}