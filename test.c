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
	t_window window;
	t_cross cross;
	double deltax;
	double deltay;
	
	ft_init_window(&window);
	i = 0;
	if (data->win_ptr == NULL)
		return (1);
	render_rect(&data->img, (t_rect){0, 0, WIN_WIDTH, (WIN_HEIGHT/2), SKY_PIXEL});
	render_rect(&data->img, (t_rect){0, (WIN_HEIGHT/2), WIN_WIDTH, (WIN_HEIGHT/2), FLOOR_PIXEL});
	while (i < WIN_WIDTH)
	{
		ft_ray_lenght(window, i, data, &cross);
		data->wall_size = floor(GRID * window.dpp / cross.dist);
		ft_texture(data, ft_get_tex(data), cross, i);
		i++;
	}
	i = 0;
	/*while (cross.i >= 1 && cross.sprite[cross.i].dist < cross.dist)
	{
		cross.i--;
		cross.sprite[cross.i].size = floor(GRID * window.dpp / cross.sprite[cross.i].dist);
		ft_sprite(data, cross, i);
		}*/
	while(i < data->nbs)
	{
		if (data->spritel[i].is_visible == 1)
		{
			deltax = data->Px - data->spritel[i].coord.x;
			deltay = data->Py - data->spritel[i].coord.y;
			data->spritel[i].dist = hypot(deltax, deltay);
			data->spritel[i].size = floor(GRID * window.dpp / data->spritel[i].dist);
			data->spritel[i].angle = (atan(fabs(deltay / deltax)) * (180 / PI));
			if (deltax < 0 && deltay > 0) 
				data->spritel[i].angle = 0 + data->spritel[i].angle;
			else if (deltax > 0 && deltay > 0)
				data->spritel[i].angle = 180 - data->spritel[i].angle;
			else if (deltax > 0 && deltay < 0)
				data->spritel[i].angle = 180 + data->spritel[i].angle;
			else 
				data->spritel[i].angle = 360 - data->spritel[i].angle;
			ft_sprite(data, i);
			data->spritel[i].is_visible = 0;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->img.mlx_img, 0, 0);
	return (0);
}

int	main(void)
{
	t_data	data;
       	int i = 0;	
	t_tex *tab;
	
	tab = (t_tex *)malloc(sizeof(t_tex) * 6);
	ft_init_data(&data);
	if (data.mlx_ptr == NULL)
		return (MLX_ERROR);
	tab[0] = ft_init_texture(&data, "img/east.xpm");
	tab[1] = ft_init_texture(&data, "img/west.xpm");
	tab[2] = ft_init_texture(&data, "img/north.xpm");
	tab[3] = ft_init_texture(&data, "img/south.xpm");
	tab[4] = ft_init_texture(&data, "img/sprite.xpm");
	tab[5] = ft_init_texture(&data, "img/other.xpm");

	while (i < 6)
	{
		data.tab[i] = tab[i];
		i++;
	}
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
	i = 0;
	while (i < 6)
	{
		mlx_destroy_image(data.mlx_ptr, data.tab[i].img.mlx_img);
		i++;
	}
	mlx_destroy_image(data.mlx_ptr, data.img.mlx_img);
	mlx_destroy_display(data.mlx_ptr);
	free(data.mlx_ptr);
	printf("fermeture\n");
}
