#include "rt.h"
#include <stdlib.h>
#include "mlx.h"

void	texture_img_call(t_texture *texture, char *path, void *mlx_ptr)
{
	int ignore;
	int	*temp;
	int	x;
	int	y;

	y = 0;
	texture->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &texture->width, &texture->height);
	temp = (int *)mlx_get_data_addr(texture->img_ptr, &ignore, &texture->size_line, &ignore);
	texture->texture_data = malloc((sizeof(int *)) * texture->height);
	while (y < texture->height)
		texture->texture_data[y++] = malloc(sizeof(int) * texture->width);
	y = 0;
	while (y < texture->height)
	{
		x = 0;
		while (x < texture->width)
		{
			texture->texture_data[y][x] = temp[x + y * texture->size_line / 4];
			x++;
		}
		y++;
	}
	mlx_destroy_image(mlx_ptr, texture->img_ptr);
}

void	texture_arr_init(t_rt *unit)
{
	int	texture_count;

	texture_count = 4;
	unit->conf.texture = (t_texture *)malloc(sizeof(t_texture) * texture_count);
	texture_img_call(&unit->conf.texture[0], "./texture/Checkerboard.xpm", unit->mlx_ptr);
	texture_img_call(&unit->conf.texture[1], "./texture/earthmap.xpm", unit->mlx_ptr);
	texture_img_call(&unit->conf.texture[2], "./texture/1000.xpm", unit->mlx_ptr);
	texture_img_call(&unit->conf.texture[3], "./texture/F_434.xpm", unit->mlx_ptr);
}

void	get_texture_img(t_ray *ray, t_rt_conf conf, enum e_texture_type type)
{
	int color;

	color = conf.texture[type].texture_data[(int)ray->y % conf.texture[type].height][(int)ray->x % conf.texture[type].width];
	ray->rec.bump_color.x = get_r(color) / 255.9900 * 0.8;
	ray->rec.bump_color.y = get_g(color) / 255.9900;
	ray->rec.bump_color.z = get_b(color) / 255.9900 * 0.8;
	ray->rec.intersec_normal = (t_vec3)ray->rec.bump_color;
}
/*
void	texture_free()
{

}