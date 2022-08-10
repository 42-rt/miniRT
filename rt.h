/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:16:26 by jkong             #+#    #+#             */
/*   Updated: 2022/08/10 21:38:14 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include "parser.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef unsigned int	t_pixel;

enum e_bit_map_constant
{
	BIT_COUNT = 8
};

typedef struct s_camera
{
	t_vec3	origin;
	t_vec3	direction;
}	t_camera;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	double	t_min;
	double	t_max;
}	t_ray;

typedef struct s_hit
{
	t_vec3	collision;
	t_vec3	next_direction;
	double	t;
}	t_hit;

typedef int				t_ray_hit_func(void *self, t_ray *r, t_hit *out);

typedef struct s_ambient_conf
{
	double	ratio;
	t_vec3	color;
}	t_ambient_conf;

typedef struct s_camera_conf
{
	t_vec3	origin;
	t_vec3	direction;
	double	fov;
}	t_camera_conf;

typedef struct s_list_light
{
	struct s_list_light	*next;
	t_vec3				origin;
	double				bright;
	t_vec3				color;
}	t_list_light;

enum e_object_type
{
	OBJ_INVALID,
	OBJ_SPHERE,
	OBJ_PLANE,
	OBJ_CYLINDER,
	OBJ_CONE,
	OBJ_HYPERBOLOID,
	OBJ_PARABOLOID,
};

typedef struct s_list_object
{
	struct s_list_object	*next;
	enum e_object_type		type;
	t_vec3					origin;
	t_vec3					direction;
	double					width;
	double					height;
	t_vec3					color;
	t_ray_hit_func			*on_hit;
}	t_list_object;

typedef struct s_rt_conf
{
	char			*name;
	t_vec3			window_size;
	t_ambient_conf	ambient;
	t_camera_conf	camera;
	t_list_light	*lights;
	t_list_object	*objects;
}	t_rt_conf;

typedef struct s_input_sys
{
	int	pressed;
	int	latest_x;
	int	latest_y;
}	t_input_sys;

typedef struct s_rt
{
	void		*mlx_ptr;
	char		*path;
	t_entry		*entry;
	t_rt_conf	conf;
	int			win_size_x;
	int			win_size_y;
	void		*win_ptr;
	void		*img_ptr;
	t_input_sys	input;
	int			update_posted;
}	t_rt;

void	fill_image(t_rt *unit, unsigned char byte);
void	put_pixel(t_rt *unit, int x, int y, int color);
void	refresh_window(t_rt *unit);

void	set_hook(t_rt *unit);

t_vec3	vec3_neg(t_vec3 vec);
double	vec3_length_sq(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_add(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_multiple(double lhs, t_vec3 rhs);
double	vec3_product(t_vec3 lhs, t_vec3 rhs);

t_vec3	vec3_cross(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_rotate_yaw(t_vec3 vec, double yaw);
t_vec3	vec3_rotate_pitch(t_vec3 vec, double pitch);
t_vec3	vec3_rotate_roll(t_vec3 vec, double roll);

int		try_eval(char *path, t_entry **out);

int		get_vec2(t_entry *ent, const char *key, t_vec3 *out);
int		get_vec3(t_entry *ent, const char *key, t_vec3 *out);

int		get_conf(t_entry *ent, t_rt_conf *out);
void	dispose_conf(t_rt_conf *in);

#endif
