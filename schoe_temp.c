#include "rt.h"
#include <math.h>
#include "libft.h"

int	create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	distance_check(t_ray *ray,	double min_ans, double max_ans)
{
	double	root;

	root = min_ans;
	if (ray->root_max < root || ray->root_min > root)
	{
		root = max_ans;
		if (ray->root_max < root || ray->root_min > root)
			return (0);
	}
	ray->root_max = root;
	ray->rec.root = root;
	return (1);
}

t_color3	get_diffuse_color(t_ray *ray, t_list_light *lights)
{
	double		kd;
	t_color3	color;

	ray->rec.light_dir = vunit(vminus(lights->origin, ray->rec.intersec_point));
	kd = vdot(ray->rec.light_dir, ray->rec.intersec_normal);
	if (kd < 0.0)
		kd = 0.0;
	color = vmult(vmult(lights->color, lights->bright), kd);
	return (color);
}

t_ray	shadow_check_ray(t_ray *ray, t_list_light *light)
{
	t_ray	temp;

	temp.origin = vplus(ray->rec.intersec_point, ray->rec.intersec_normal);
	temp.direction = vminus(light->origin, ray->rec.intersec_point);
	temp.root_min = 0;
	temp.root_max = vlength(temp.direction);
	temp.direction = vunit(temp.direction);
	temp.rec.hit_flag = 1;
	return (temp);
}

void	mirror_ray(t_ray *ray)
{
	ray->origin = vplus(ray->rec.intersec_point, ray->rec.intersec_normal);
	ray->direction = vmult(ray->direction, -1);
	ray->direction = vminus(vmult(vmult(ray->rec.intersec_normal, \
					(vdot(ray->direction, ray->rec.intersec_normal))), 2.0), ray->direction);
	ray->direction = vunit(ray->direction);
	ray->root_min = 0;
	ray->root_max = LIGHT_MAX_LENGTH - ray->root_max;
	ft_memset(&(ray->rec), 0, sizeof(t_hit));
}

t_color3	get_specular_color(t_ray *ray, t_list_light *lights)
{
	t_point3	reflect_light;
	double		spec;
	t_color3	color;

	reflect_light = vminus(vmult(vmult(ray->rec.intersec_normal, \
	(vdot(ray->rec.light_dir, ray->rec.intersec_normal))), 2.0), ray->rec.light_dir);
	spec = vdot(reflect_light, vmult(ray->direction, -1.0));
	if (spec < 0.0)
		spec = 0.0;
	spec = powf(spec, 32);
	color = vmult(vmult(lights->color, lights->bright), spec);
	return (color);
}

void	shadow_check_sp(t_rt_conf conf, t_ray *ray)
{
	t_list_light	*temp_light;
	t_ray			ray_hit_check;

	temp_light = conf.lights;
	while (temp_light)
	{
		ray_hit_check = shadow_check_ray(ray, temp_light);
		if (world_hit_check(conf, &ray_hit_check) == -1)
		{
			ray->rec.Diffuse = vplus(ray->rec.Diffuse, get_diffuse_color(ray, temp_light));
			ray->rec.Specular = vplus(ray->rec.Specular, get_specular_color(ray, temp_light));
		}
		temp_light = temp_light->next;
	}
}

int	hit_sphere(t_ray *ray, t_rt_conf conf, t_list_object sp, int deep)
{
	t_color3	ambient;

	if (!hit_check_sp(ray, sp))
		return (0);
	ray->rec.hit_flag = 1;
	ray->rec.intersec_point = vplus(ray->origin, vmult(ray->direction, ray->rec.root));
	ray->rec.intersec_normal = vunit(vminus(ray->rec.intersec_point, sp.origin));
	if (deep == 0)
	{
		mirror_ray(ray);
		wolrd_draw(conf, ray, 1);
		return (1);
	}
	shadow_check_sp(conf, ray);
	ambient = vmult(conf.ambient.color, conf.ambient.ratio);
	ray->rec.fin_color = vmin(vplus(sp.color, vplus(vplus(ambient, ray->rec.Diffuse), \
						ray->rec.Specular)), (t_color3){255.99, 255.99, 255.99});
	return (1);
}

int	wolrd_draw(t_rt_conf conf, t_ray *ray, int deep)
{
	t_list_object	*temp;

	temp = conf.objects;
	while (temp)
	{
		if (temp->type == OBJ_SPHERE)
			hit_sphere(ray, conf, *temp, 1);
	/*	else if (conf->objects->type == OBJ_PLANE &&)
			return (OBJ_PLANE);
		else if (conf->objects->type == OBJ_CYLINDER &&)
			return (OBJ_CYLINDER);
		else if (conf->objects->type == OBJ_CONE &&)
			return (OBJ_CONE);
		else if (conf->objects->type == OBJ_HYPERBOLOID &&)
			return (OBJ_HYPERBOLOID);*/
		else if (temp->type == OBJ_CONE)
			hit_sphere(ray, conf, *temp, deep);
		temp = temp->next;
	}
	return (ray->rec.hit_flag);
}

int	hit_check_sp(t_ray *ray, t_list_object sp)
{
	t_vec3	oc;
    double	a;
    double	b;
    double	c;
    double	discriminant;

    oc = vminus(ray->origin, sp.origin);
    a = vdot(ray->direction, ray->direction);
    b = 2 * vdot(oc, ray->direction);
    c = vdot(oc, oc) - sp.width * sp.width;
    discriminant = (b * b) - (4 * a * c);
	if (discriminant < 0.0)
		return (0);
	if (!distance_check(ray, (-b - sqrt(discriminant))/2/a, (-b + sqrt(discriminant))/2/a))
		return (0);
	return (1);
}

int	world_hit_check(t_rt_conf conf, t_ray *ray)
{
	t_list_object	*temp;

	temp = conf.objects;
	while (temp)
	{
		if ((conf.objects->type == OBJ_SPHERE || conf.objects->type == OBJ_CONE) && hit_check_sp(ray, *temp))
			return (OBJ_SPHERE);
	/*	else if (conf->objects->type == OBJ_PLANE &&)
			return (OBJ_PLANE);
		else if (conf->objects->type == OBJ_CYLINDER &&)
			return (OBJ_CYLINDER);
		else if (conf->objects->type == OBJ_CONE &&)
			return (OBJ_CONE);
		else if (conf->objects->type == OBJ_HYPERBOLOID &&)
			return (OBJ_HYPERBOLOID);
		else if (conf->objects->type == OBJ_PARABOLOID &&)
			return (OBJ_PARABOLOID);*/
		temp = temp->next;
	}
	return (-1);
}

t_ray	get_viewport_ray(t_camera_conf cam, double x, double y)
{
	t_ray	ray;
	t_vec3	w;
	t_vec3	h;
	t_point3	view_vec;

	ray.origin = cam.origin;
	w = vmult(cam.r_normal, x);
	h = vmult(cam.up_normal, y);
	view_vec = vplus(cam.leftdown_coner, w);
	view_vec = vplus(view_vec, h);
	ray.direction = vunit(vminus(view_vec, ray.origin));
	ray.root_min = 0;
	ray.root_max = LIGHT_MAX_LENGTH;
	ray.rec.hit_flag = 0;
	ft_memset(&ray.rec, 0, sizeof(t_hit));
	return (ray);
}

void	cam_init(t_camera_conf *cam)
{
	t_vec3	vec_y;
	t_vec3	vec_z;
	t_point3	temp_coner;

	vec_y = (t_vec3){0, 1, 0};
	vec_z = (t_vec3){0, 0, -1};
	if (vlength(vcross(cam->direction, vec_y)))
		cam->r_normal = vunit(vcross(cam->direction, vec_y));
	else
		cam->r_normal = vunit(vcross(cam->direction, vec_z));
	cam->up_normal = vunit(vcross(cam->r_normal, cam->direction));
	cam->fov = cam->fov / 180.00000 * M_PI;
	cam->focal_len = (double)WIDTH / 2 / tan(cam->fov / 2);
	temp_coner = vplus(cam->origin, vmult(cam->direction, cam->focal_len));
	temp_coner = vplus(temp_coner, vmult(cam->r_normal, -(double)((WIDTH - 1) / 2)));
	cam->leftdown_coner = vplus(temp_coner, vmult(cam->up_normal, -(double)((HEIGT - 1) / 2)));
}
