/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jkong <jkong@student.42seoul.kr>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/01 15:16:26 by jkong             #+#    #+#             */
/*   Updated: 2022/08/05 20:16:54 by jkong            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include <unistd.h>
# include "parser.h"

typedef struct s_vec2
{
	double	x;
	double	y;
}	t_vec2;

typedef struct s_vec3
{
	double	x;
	double	y;
	double	z;
}	t_vec3;

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
}	t_list_object;

typedef struct s_rt_conf
{
	char			*name;
	t_vec2			window_size;
	t_ambient_conf	ambient;
	t_camera_conf	camera;
	t_list_light	*lights;
	t_list_object	*objects;
}	t_rt_conf;

int	get_vec2(t_entry *ent, const char *key, t_vec2 *out);
int	get_vec3(t_entry *ent, const char *key, t_vec3 *out);

int	get_conf(t_entry *ent, t_rt_conf *out);

#endif
