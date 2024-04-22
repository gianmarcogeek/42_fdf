#include "../include/fdf.h"

int	close_and_free(int keysys, t_vars *vars)
{
	if(keysys == 0xff1b)
	{
		mlx_destroy_image(vars->mlx, vars->img);
		mlx_destroy_window(vars->mlx, vars->win);
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
		exit(1);
	}
	return (0);
}



int	main(void)
{
	t_vars	vars;
	t_data	img;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 700, 700, "Let's go!");
	img.img = vars.img = mlx_new_image(vars.mlx, 700, 700);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_lenght, &img.endian);

	int colore = create_trgb(0, 255, 0, 0);
	int colore2 = create_trgb(0, 0, 255, 0);

	draw_faded_square(&img, 400, 150, 250, colore, colore2);
	draw_square(&img, 350, 150, 200, colore);

	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	
	mlx_key_hook(vars.win, close_and_free, &vars);
	mlx_loop(vars.mlx);
}
