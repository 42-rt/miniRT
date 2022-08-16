/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:16:26 by jkong             #+#    #+#             */
/*   Updated: 2022/08/16 12:39:49 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include "parser.h"

#define	WIDTH 2560
#define HEIGT 1440
#define	LIGHT_MAX_LENGTH 100000

struct s_vec3
{
	double	x;
	double	y;
	double	z;
};

typedef struct s_vec3	t_vec3;
typedef struct s_vec3	t_point3;
typedef struct s_vec3	t_color3;

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

typedef struct s_hit
{
	t_vec3		collision;
	t_vec3		next_direction;
	t_point3	intersec_point;
	t_vec3		intersec_normal;
	int			in_out_check;
	int			hit_flag;
	double		root;
	t_point3	light_dir;
	t_color3	Diffuse;
	t_color3	Specular;
	t_color3	fin_color;
	t_color3	bump_color;
}	t_hit;

typedef struct s_ray
{
	t_vec3	origin;
	t_vec3	direction;
	double	root_min;
	double	root_max;
	t_hit	rec;
	double	x;
	double	y;
}	t_ray;

typedef int				t_ray_hit_func(void *self, t_ray *r, t_hit *out);

typedef struct s_ambient_conf
{
	double	ratio;
	t_vec3	color;
}	t_ambient_conf;

typedef struct s_camera_conf
{
	t_vec3		origin;
	t_vec3		direction;


	t_vec3		r_normal;
	t_vec3		up_normal;
	t_point3	leftdown_coner;
	double		fov;
	double		focal_len;
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
	double					width;//radius
	double					height;
	t_vec3					color;
	t_ray_hit_func			*on_hit;
}	t_list_object;

enum e_texture_type
{
	Checker_board,
	Earth,
	moon,
	circuit,
};

typedef	struct s_texture
{
	int		**texture_data;
	int		width;
	int		height;
	int		size_line;
	void	*img_ptr;
} t_texture;

typedef struct s_rt_conf
{
	char			*name;
	t_vec3			window_size;
	t_ambient_conf	ambient;
	t_camera_conf	camera;
	t_list_light	*lights;
	t_list_object	*objects;
	t_texture		*texture;
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

//schoe add
void	cam_init(t_camera_conf *cam);
t_ray	get_viewport_ray(t_camera_conf cam, double x, double y);
int	distance_check(t_ray *ray,	double min_ans, double max_ans);
t_color3 get_diffuse_color(t_ray *ray, t_list_light *lights);
t_ray	shadow_check_ray(t_ray *ray, t_list_light *light);
t_color3 get_specular_color(t_ray *ray, t_list_light *lights);
int	hit_sphere(t_ray *ray, t_rt_conf conf, t_list_object sp, int deep);
int	wolrd_draw(t_rt_conf conf, t_ray *ray, int deep);
int	hit_check_sp(t_ray *ray, t_list_object sp);
int	world_hit_check(t_rt_conf conf, t_ray *ray);
void	shadow_check_sp(t_rt_conf conf, t_ray *ray);
void	mirror_ray(t_ray *ray);
t_ray	shadow_check_ray(t_ray *ray, t_list_light *light);
//plane
int	hit_check_pl(t_ray *ray, t_list_object pl);
int	hit_plane(t_ray *ray, t_rt_conf conf, t_list_object pl, int deep);
//texture
void	texture_img_call(t_texture *texture, char *path, void *mlx_ptr);
void	texture_arr_init(t_rt *unit);
void	get_texture_img(t_ray *ray, t_rt_conf conf, enum e_texture_type type);
//color
int	create_trgb(int t, int r, int g, int b);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);
t_color3    ray_color(double r);
//temp_vector
double		vlength2(t_vec3 vec);
double		vlength(t_vec3 vec);
t_vec3		vplus(t_vec3 vec, t_vec3 vec2);
t_vec3		vminus(t_vec3 vec, t_vec3 vec2);
t_vec3		vmult(t_vec3 vec, double t);
t_vec3		vmult_(t_vec3 vec, t_vec3 vec2);
t_vec3		vdivide(t_vec3 vec, double t);
double		vdot(t_vec3 vec, t_vec3 vec2);
t_vec3		vcross(t_vec3 vec, t_vec3 vec2);
t_vec3		vunit(t_vec3 vec);
t_vec3		vmin(t_vec3 vec1, t_vec3 vec2);
t_vec3		vmax(t_vec3 vec1, t_vec3 vec2);

#endif
