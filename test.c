#include "cub3d.h"

void	img_pix_put(t_img *img, int x, int y, int color)
{
	char    *pixel;
	int		i;

	i = img->bpp - 8;
	pixel = img->addr + (y * img->line_len + x * (img->bpp / 8));
	while (i >= 0)
	{
		/* big endian, MSB is the leftmost bit */
		if (img->endian != 0)
			*pixel++ = (color >> i) & 0xFF;
		/* little endian, LSB is the leftmost bit */
		else
			*pixel++ = (color >> (img->bpp - 8 - i)) & 0xFF;
		i -= 8;
	}
}

/* The x and y coordinates of the rect corresponds to its upper left corner. */

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

void	render_background(t_img *img, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_HEIGHT)
	{
		j = 0;
		while (j < WIN_WIDTH)
		{
			img_pix_put(img, j++, i, color);
		}
		++i;
	}
}

int	handle_keypress(int keysym, t_data *data)
{
	double delta_x;
	double delta_y;
	
	if (keysym == XK_Escape)
	{
		mlx_destroy_window(data->mlx_ptr, data->win_ptr);
		data->win_ptr = NULL;
	}
	if (keysym == XK_Right)
	{
		data->dir -= 5;
		if (data->dir < 0)
			data->dir += 360;
	}
	if (keysym == XK_Left)
	{
		data->dir += 5;
		if (data->dir >= 360)
			data->dir -= 360;
	}
	delta_x = (cos(data->dir * DEG_CONV) * 5);
	delta_y = (-sin(data->dir * DEG_CONV) * 5);
	if (keysym == XK_z)
	{ 
		data->Px += delta_x;
		data->Py += delta_y;
	}
	if (keysym == XK_s)
	{
		data->Px -= delta_x;
		data->Py -= delta_y;
	}
	if (keysym == XK_q)
	{
		data->Px += delta_y;
		data->Py -= delta_x;
	}
	if (keysym == XK_d)
	{
		data->Px -= delta_y;
		data->Py += delta_x;
	}
	printf("dir: %d\n", data->dir);
	return (0);
}

int	render(t_data *data)
{
	int i;
	int color;
	double wall_size;
	t_window window;
	int start_h;

	ft_init_window(&window);
	i = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_background(&data->img, WHITE_PIXEL);
	render_rect(&data->img, (t_rect){0, 0, WIN_WIDTH, (WIN_HEIGHT/2), RED_PIXEL});
	while (i < WIN_WIDTH)
	{
		wall_size = ft_ray_lenght(window, i, data);
		if (wall_size > WIN_HEIGHT)
			wall_size = WIN_HEIGHT;
		start_h = (int)((WIN_HEIGHT/2) - (wall_size/2));
		color = ft_get_wall(data);
		render_rect(&data->img, (t_rect){(i), start_h, 1, (int)wall_size, color});
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);

	return (0);
}

int	main(void)
{
	t_data	data;
	data.Px = 160;
	data.Py = 160;
	data.dir = 10;
	data.hit = 0;
	data.mlx_ptr = mlx_init();
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	printf("initialisation\n");
	data.win_ptr = mlx_new_window(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "my window");
	if (data.win_ptr == NULL)
	{
		free(data.win_ptr);
		return (MLX_ERROR);
	}

	/* Setup hooks */ 
	data.img.mlx_img = mlx_new_image(data.mlx_ptr, WIN_WIDTH, WIN_HEIGHT);

	data.img.addr = mlx_get_data_addr(data.img.mlx_img, &data.img.bpp,
			&data.img.line_len, &data.img.endian);

	mlx_loop_hook(data.mlx_ptr, &render, &data);
	mlx_hook(data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &data);

	mlx_loop(data.mlx_ptr);

	/* we will exit the loop if there's no window left, and execute this code */
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
}
