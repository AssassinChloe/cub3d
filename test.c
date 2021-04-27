#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		if (img->endian != 0)
			*pixel++ = (color >> i);
		else
			*pixel++ = (color >> (img->bpp - 8 - i));
		i -= 8;
	}
}

int render_rect(t_img *img, t_rect rect)
{
	int	i;
	int j;

	i = rect.y;
	while (i < rect.y + rect.height)
	{
		j = rect.x;
		while (j < rect.x + rect.width)
			img_pix_put(img, j++, i, rect.color);
		++i;
	}
	return (0);
}

int	render(t_data *data)
{
	int i;
	int color;
	t_window window;
	int start_h;
	t_cross cross;
	t_tex east;
	t_tex west;
	t_tex north;
	t_tex south;

	ft_init_window(&window);
	ft_init_texture(data, "east.xpm", &east);
	ft_init_texture(data, "west.xpm", &west);
	ft_init_texture(data, "north.xpm", &north);
	ft_init_texture(data, "south.xpm", &south);
	i = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_rect(&data->img, (t_rect){0, 0, WIN_WIDTH, (WIN_HEIGHT/2), SKY_PIXEL});
	render_rect(&data->img, (t_rect){0, (WIN_HEIGHT/2), WIN_WIDTH, (WIN_HEIGHT/2), FLOOR_PIXEL});
	while (i < WIN_WIDTH)
	{
		cross = ft_ray_lenght(window, i, data);
		ft_texture(data, ft_get_tex(data, &east, &west, &north, &south), cross, i);
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;
	
	ft_init_data(&data);
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	
	printf("initialisation\n");
	
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}
	
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);
//	mlx_hook(data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease, &data);
	mlx_loop(data.mlx_ptr);

	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	printf("fermeture\n");
}
