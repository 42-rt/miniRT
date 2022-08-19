/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: schoe <schoe@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:16:26 by jkong             #+#    #+#             */
/*   Updated: 2022/08/19 16:43:26 by schoe            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# ifndef MIN_RAY_LENGTH
#  define MIN_RAY_LENGTH 1.0e-8
# endif

# ifndef MAX_RAY_LENGTH
#  define MAX_RAY_LENGTH 1.0e6
# endif

# include <unistd.h>
# include "parser.h"

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

typedef t_vec3					t_pt3;
typedef t_vec3					t_rgb;

typedef unsigned int			t_pixel;

enum e_bit_map_constant
{
	BIT_COUNT = 8
};

typedef struct s_camera
{
	t_pt3	origin;
	t_pt3	left_top;
	t_vec3	horizontal;
	t_vec3	vertical;
}	t_camera;

typedef struct s_list_light		t_list_light;
typedef struct s_list_object	t_list_object;

typedef struct s_ray
{
	t_pt3	origin;
	t_vec3	direction;
	double	t_min;
	double	t_max;
	double	x;
	double	y;
	t_pt3	view_point;
}	t_ray;

typedef struct s_hit
{
	double			t;
	t_pt3			collision;
	t_vec3			normal;
	t_list_object	*obj;
}	t_hit;

typedef int						t_ray_hit_func(
	void *self,
	t_ray *ray,
	t_hit *out
);

typedef struct s_ambient_conf
{
	double	ratio;
	t_rgb	color;
}	t_ambient_conf;

typedef struct s_camera_conf
{
	t_pt3	origin;
	t_vec3	direction;
	double	fov;
}	t_camera_conf;

struct s_list_light
{
	t_list_light	*next;
	t_pt3			origin;
	double			bright;
	t_rgb			color;
};

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

struct s_list_object
{
	t_list_object		*next;
	enum e_object_type	type;
	t_pt3				origin;
	t_vec3				direction;
	double				width;
	double				height;
	t_rgb				color;
	t_ray_hit_func		*on_hit;
};

enum e_texture_type
{
	Checker_board,
	F_1000,
	circute,
	block,
};

typedef	struct s_texture
{
	int		**texture_data;
	int		width;
	int		height;
	int		size_line;
	void	*img_ptr;
	int		texture_max_count;
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
	t_camera	camera;
	t_input_sys	input;
	int			update_posted;
}	t_rt;

void	camera_init(t_rt_conf *conf, t_camera *out);
void	ray_from_camera(t_camera *cam, double x, double y, t_ray *out);
void	ray_to_light(t_pt3 pt, t_list_light *light, t_ray *out);
int		ray_try_doing_hit(t_list_object *world, t_ray *ray, t_hit *hit);

t_vec3	ray_color(t_rt *unit, t_ray *ray, int depth);

void	fill_image(t_rt *unit, unsigned char byte);
void	put_pixel(t_rt *unit, int x, int y, int color);
void	refresh_window(t_rt *unit);

void	set_hook(t_rt *unit);

double	second_df(t_vec3 vec);
double	second_df_half(t_vec3 vec);
double	second_qe(t_vec3 vec, double d);
double	second_qe_half(t_vec3 vec, double quarter_d);

t_vec3	vec3_neg(t_vec3 vec);
t_vec3	vec3_add(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_mul(double lhs, t_vec3 rhs);
t_vec3	vec3_mul_v(t_vec3 lhs, t_vec3 rhs);
double	vec3_len_sq(t_vec3 vec);

t_vec3	vec3_sub(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_div(double lhs, t_vec3 rhs);
double	vec3_len(t_vec3 vec);
t_vec3	vec3_unit(t_vec3 vec);

double	vec3_dot(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_cross(t_vec3 lhs, t_vec3 rhs);
t_vec3	vec3_rotate_yaw(t_vec3 vec, double yaw);
t_vec3	vec3_rotate_pitch(t_vec3 vec, double pitch);
t_vec3	vec3_rotate_roll(t_vec3 vec, double roll);

int		try_eval(char *path, t_entry **out);

int		get_vec2(t_entry *ent, const char *key, t_vec3 *out);
int		get_vec3(t_entry *ent, const char *key, t_vec3 *out);

int		get_conf(t_entry *ent, t_rt_conf *out);
void	dispose_conf(t_rt_conf *in);
//texture
void	texture_img_call(t_texture *texture, char *path, void *mlx_ptr);
void	texture_arr_init(t_rt *unit);
t_vec3	get_texture_normal(t_rgb color);
void	texture_free(t_rt *unit);
t_rgb	get_texture_color(t_hit hit, t_rt_conf conf, enum e_texture_type type);
//color
int	get_t(int trgb);
int	get_r(int trgb);
int	get_g(int trgb);
int	get_b(int trgb);
int	create_trgb(int t, int r, int g, int b);
#endif
