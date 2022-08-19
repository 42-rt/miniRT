#include "rt.h"
#include <stdlib.h>
#include "mlx.h"
#include <math.h>
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
	unit->conf.texture[0].texture_max_count = texture_count;
//	texture_img_call(&unit->conf.texture[0], "./texture/Checkerboard.xpm", unit->mlx_ptr);
	texture_img_call(&unit->conf.texture[0], "./texture/check.xpm", unit->mlx_ptr);
	texture_img_call(&unit->conf.texture[1], "./texture/F_1000.xpm", unit->mlx_ptr);
	texture_img_call(&unit->conf.texture[2], "./texture/F_434.xpm", unit->mlx_ptr);
	texture_img_call(&unit->conf.texture[3], "./texture/block.xpm", unit->mlx_ptr);
}

t_vec3	get_texture_normal(t_rgb color)
{
	t_rgb	bump_color;

	bump_color.x = color.x / 255.9900;
	bump_color.y = color.y / 255.9900;
	bump_color.z = color.z / 255.9900;
	return(vec3_unit(bump_color));
}//length에 따라 배율 조절

t_rgb	get_texture_color(t_hit hit, t_rt_conf conf, enum e_texture_type type)
{
	int 	color;
	t_rgb	bump_color;
	t_pt3	z_cross;

	z_cross = vec3_cross(hit.collision, (t_vec3){0, 0, 1});
	if ((hit.collision.y < 0.0 && hit.collision.x < 0.0 && hit.collision.z < 0.0) \
		|| (hit.collision.y < 0.0 && hit.collision.x > 0.0 && hit.collision.z > 0.0) \
		|| (hit.collision.y > 0.0 && hit.collision.x > 0.0 && hit.collision.z < 0.0) \
		|| (hit.collision.y > 0.0 && hit.collision.x < 0.0 && hit.collision.z > 0.0))
	{
		color = conf.texture[type].texture_data\
		[conf.texture[type].height -1 -((int)(fabs(z_cross.y)) % conf.texture[type].height)]\
		[conf.texture[type].width -1 -((int)(fabs(z_cross.x)) % conf.texture[type].width)];	
	}
	else
		color = conf.texture[type].texture_data\
		[(int)((fabs(z_cross.y))) % conf.texture[type].height]\
		[(int)((fabs(z_cross.x))) % conf.texture[type].width];
	bump_color.x = get_r(color);
	bump_color.y = get_g(color);
	bump_color.z = get_b(color);
	return((bump_color));
}

void	texture_free(t_rt *unit)
{
	int	i;
	int	free_index;

	i = 0;
	while (i < unit->conf.texture[0].texture_max_count)
	{
		free_index = 0;
		while (free_index < unit->conf.texture[i].height)
			free(unit->conf.texture[i].texture_data[free_index++]);
		free(unit->conf.texture[i].texture_data);
		i++;
	}
	free(unit->conf.texture);
}