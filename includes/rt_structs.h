/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 11:49:00 by vpaladii          #+#    #+#             */
/*   Updated: 2018/07/07 11:49:00 by vpaladii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

# include <OpenCL/opencl.h>

enum	e_error {NUM_OF_ARG, ERROR, CAM_ERROR};
enum	e_figures {SPHERE, CYLINDER, CONE, PLANE, ELLIPSOID};
enum	e_lights {AMBIENT, POINT, DIRECT};

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_channel
{
	float			red;
	float			green;
	float			blue;
}					t_channel;

typedef struct	s_ray
{
	cl_float3	origin;
	cl_float3	direction;
}				t_ray;

typedef struct		s_coord_sys
{
	cl_float3		b_x;
	cl_float3		b_y;
	cl_float3		b_z;
}					t_coord_sys;

typedef struct	s_camera
{
	cl_float3		origin;
	t_coord_sys		basis;
	t_coord_sys     initial_basis;
	cl_float3        angle_rot;
	int			    is_set;
	double		    dest;

}				t_camera;

typedef struct		s_light // ADDED TYPE, fix
{
	int				type;
	cl_float3		origin;
	t_channel		color;
	float			intensity;
	cl_float3		direct;
	struct s_light	*next;
}					t_light;

struct s_intersect;
typedef struct		s_figure
{
	int				type;
	t_channel		color;
	cl_float3		origin;
    cl_float3		normal;
	float			radius;
    float			angle_coef;
	t_coord_sys		basis;
	float			mirror_coef;
	float			transperent_coef;
	cl_float3		axis_dimensions;//размеры осей x y z для эллипсоида
	int				bling_phong;
	struct s_figure	*next;
}					t_objects;

typedef struct		s_intersect
{
	cl_float3	    point;//точка пересечения фигуры и луча
	float			distance;
	t_objects		*fig;
	cl_float3		normal;
}					t_intersect;

typedef struct		s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				devices_num;
	cl_uint				platforms_num;
	cl_int				err;
	cl_mem				lights;
	cl_mem				objects;
	cl_mem				color;
}						t_cl;

typedef struct	s_rt
{
	SDL_Window		*window;
	SDL_Surface		*screen_surface;
	t_camera		camera;
	t_cl			cl;
	t_light			*lights;
	t_objects		*objects;
	int				reflect_rate;
	int				max_reflections;
	int				line_number;
}				t_rt;

typedef struct	s_parce
{
	char		*name;
	int			(*parce)(int, t_rt *);
}				t_parce;

#endif
