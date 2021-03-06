/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:03:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/23 21:51:51 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RT_FUNCTIONS_H
# define RT_FUNCTIONS_H

# include <OpenCL/opencl.h>
//# include <SDL.h>
//# include <SDL_ttf.h>
//# include <SDL_image.h>
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"

# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "rt_structs.h"
# include <pthread.h>

# define THREAD_MAX 20
# define FALSE 0
# define TRUE 1

# define DIVISION 0
# define MULTIPLICATION 1

# define SCR_SIZE 1000
# define OBJ_NUM 6
# define DISTANCE 1
# define DIRECT_LIGHT_IS_PARSED 15
# define POINT_LIGHT_IS_PARSED 23
# define AMBIENT_LIGHT_IS_PARSED 35
# define SPHERE_IS_PARSED 31
# define CAMERA_IS_PARSED 3
# define CONE_IS_PARSED 63
# define CYLINDER_IS_PARSED 63
# define PLANE_IS_PARSED 31
# define STEP (1.0 / SCR_SIZE)
# define SHIFT_STEP 0.2
# define LEFT_BOUND (-(SCR_SIZE / 2))
# define TOP_BOUND (-(SCR_SIZE / 2))
# define A 0
# define B 1
# define C 2
# define ANGLE (M_PI * (5) / 180.0)
# define ANGLE_IN_DEGREES(angle) (M_PI * (angle) / 180.0)

# define MAX_SRC_SIZE	0x100000
# define VEC(a1, a2, a3) (cl_float3){{a1, a2, a3}}
# define W_TITLE "RT by BOBMA_RAKETA"

# define DEEP_BLUE (SDL_Color){33, 150, 243, 0}
# define SKY_BLUE (SDL_Color){144, 202, 249, 0}
# define BLACK (SDL_Color){0, 0, 0, 0}
# define WHITE (SDL_Color){255, 255, 255, 0}

# define GUI_ALIAS_ON_BMP "gui_images/foot_bar_aliasing_on.bmp"
# define GUI_ALIAS_OFF_BMP "gui_images/foot_bar_aliasing_off.bmp"
# define GUI_SEPIA_BMP "gui_images/sepia.bmp"
# define GUI_GREYSCALE_BMP "gui_images/greyscale.bmp"
# define GUI_NEGATIVE_BMP "gui_images/negative.bmp"
# define GUI_PIXEL_BMP "gui_images/pixel.bmp"


# define dist(a, b, c, d) sqrt((double)((a - c) * (a - c) + (b - d) * (b - d)))
//# define interpolate(a, b, x) ((double)a * (double)(1.0 - (1.0 - cos(x * 3.1415927)) * 0.5) + (double)b * (double)(1.0 - cos(x * 3.1415927)) * 0.5)
//# define interpolate(a, b, x) a * (1 - x) + b * x
// ---------------------------------------------------------------------------------

unsigned int **g_wall; // GLOBAL


// ---------------------------------------------------------------------------------


/*validate directory*/
int				find_fd(char *file);
/*parcing_function directory*/
void			file_parcing(char *file, t_rt *rt_data);
void			line_reader(t_rt *rt_data, int fd, const t_parce arr[]);
void			parcer_functions(char **str, t_rt *rt_data, const t_parce arr[],
							 int fd);
void			correct_plane_normal(t_rt *rt_data);
t_coord_sys		create_coord_system(t_coord_sys basis);

int				cam_parce(int fd, t_rt *rt_data);
void			camera_data_fill(char **line, t_camera *camera, int l_num, int *flag);

int				cone_parce(int fd, t_rt *rt_data);
void			cone_data_fill(char **line, t_objects *cone, int l_num, int *flag);
void			more_cone_data_fill(char **line, t_objects *cone, int l_num, int *flag);

int				cylinder_parce(int fd, t_rt *rt_data);
void			cylin_data_fill(char **line, t_objects *cyl, int l_num, int *flag);
void			more_cylin_data_fill(char **line, t_objects *cyl, int l_num, int *flag);

int				sphere_parce(int fd, t_rt *rt_data);
void			sphere_fill(char **line, t_objects *sphere, int l_num, int *flag);

int				plane_parce(int fd, t_rt *rt_data);
void			plane_fill(char **line, t_objects *plane, int l_num, int *flag);

void			add_shape(t_rt *rt_data, t_objects *shape);
void			add_light(t_rt *rt_data, t_light *light);

int				begin_with(char *line, char *begin);
char			*trim_from(char *line, int i);

float			drob_finder(char *line, int i, int line_number);
float			str_to_float(char *line, int i, int line_number);

t_channel		parce_color(char *line, int line_number);
float			float_finder(char *line, int *i, int line_number);
cl_float3		parce_vector(char *line, int line_number);

int				light_parce(int fd, t_rt *rt_data);
void			feelings(char **line, t_light *light, int line_number, int *flag);
void			more_of_feelings(char **line, t_light *light, int line_number,
									int *flag);

//------------------------------------------------------------------------------------

void			draw_pixel(t_rt *rt, t_objects *objects, t_light *lights, t_dot pixel);
int				draw_scene(t_rt *rt_data);
void			ray_tracing(t_rt *rt_data);
t_intersect		find_closest_inter(t_cl_data cl_data, t_objects *objects, t_ray primary_ray);
t_ray			compute_ray(t_camera camera, t_dot pixel);
void			choose_intersection(t_ray primary_ray, t_intersect *tmp_inter);
void			rotating_camera(int keycode, t_rt *rt_data);
int				exit_x(t_rt *rt_data, SDL_Event *event);
int				key_down(t_rt *rt_data, SDL_Event *event);

void			event_management(t_rt *rt_data, SDL_Event *event);
t_coord_sys		init_basis_after_rot(t_rt *rt_data);
t_coord_sys		rot_matrix_about_the_axis(float angle, cl_float3 axis);

cl_float3		choose_normal(t_objects figure, cl_float3 inter);
cl_float3		find_normal_to_sphere(t_objects sphere, cl_float3 inter);
cl_float3		find_normal_to_cone(t_objects cone, cl_float3 inter);
cl_float3		find_normal_to_plane(t_objects plane, cl_float3 inter);
cl_float3		find_normal_to_cylinder(t_objects cyl, cl_float3 inter);
cl_float3		find_normal_to_ellipsoid(t_objects ellipsoid, cl_float3 inter);//new

void			handle_axis_dimensions(t_objects *ellipsoid);//new

void			add_coef(t_channel *coef1, t_channel coef2, float coef);
t_channel		find_lamp_coef(t_cl_data cl_data, t_objects *objects, t_light *current_lamp,
								t_intersect closest_inter, t_ray r, t_light *lights);
t_ray			find_light_ray(cl_float3 origin, cl_float3 end);
uint32_t		find_color(t_cl_data cl_data, t_light *lights, t_objects *objects, t_intersect closest_inter, t_ray r);

int				is_shadows_here(t_ray light_ray, cl_float3 normal, t_ray r);
int				is_figure_first_inter_by_light(t_cl_data cl_data, t_objects *objects, t_ray light_ray,
												  t_intersect closest_inter);
float			*find_cos_angle(t_ray light_ray, t_intersect closest_inter, cl_float3 normal, t_ray r);
uint32_t		find_color_hex(t_channel light_coef, t_intersect closest_inter);
uint32_t		find_color_channel(float fig_color_channel, float light_color_channel, int step);

void			set_pixel(SDL_Surface *surface, int x, int y, uint32_t color);

/* find_intersection directory */
void			sphere_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_sphere_discriminant(t_ray r, t_objects *fig, float coefficient[3]);
int				find_the_root(float coefficient[3], float discriminant, float t[2]);

void			cyl_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_cyl_discriminant(t_ray r, float radius, float *coefficient);

void			plane_find_closest_intersect(t_ray r, t_intersect *inter);

void			cone_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_cone_discriminant(t_ray r, float *coefficient, float coef);

void			ellipsoid_find_closest_intersect(t_ray r, t_intersect *inter);//new

//------------------------------------------------------------------------------------





/*error manager*/
void		error_exit(int error_name,t_rt *rt_data);
void		freesher(t_light *light, t_objects *shapes);
void		error_caster(int line_number, char *s1, char *s2);
/*math_functions*/
cl_float3	matrix_mult_vect(t_coord_sys a, cl_float3 v);
t_coord_sys	matrix_mult_matrix(t_coord_sys a, t_coord_sys b);//new
t_coord_sys	count_inverse_matrix(t_coord_sys a);
t_coord_sys	create_coord_system(t_coord_sys basis);
void		normalize_basis(t_coord_sys *a);

cl_float3	vect_diff(cl_float3 v1, cl_float3 v2);
cl_float3	vect_sum(cl_float3 v1, cl_float3 v2);
cl_float3	vect_mult_scalar(cl_float3 v1, float multiplier);
cl_float3	vect_cross_product(cl_float3 a, cl_float3 b);
float		vect_scalar_mult(cl_float3 v1, cl_float3 v2);
cl_float3	normalize_vector(cl_float3 a);
cl_float3	scale_vector(cl_float3 v, int flag, cl_float3 scale_coef);

float		find_square(float a);
float		distance(cl_float3 v1, cl_float3 v2);
float		length(cl_float3 v);

void		cl_start(t_rt *rt);
void		cl_init(t_rt *rt);

t_channel	int_to_channels(int col);
void		get_texture(t_intersect *closest_inter, t_cl_data cl_data);
void 		load_texture(SDL_Surface **textures, int index, char *path);

void		draw_clicked_info(t_rt *rt_data);
void		draw_bar(t_rt *rt_data);

void		init_gui_bmps(t_rt	*rt_data);
void		init_foot_gui_bmps(t_rt *rt_data);
void		init_bar_positions(t_rt	*rt_data);
void		draw_gui(t_rt *rt_data);

void		*draw_strings(void *thread_data_void);
void		set_tread_param(t_rt *scene, t_thread_data *thread_num);

void		change_sphere(t_objects *object, int arrow);
void		change_cylinder(t_objects *object, int arrow);
void		change_cone(t_objects *object, int arrow);
void		change_object(t_objects *object, int arrow);

int			check_arrow_type(SDL_Event *event);
void		gui_interaction_event(t_rt *rt_data, SDL_Event *event);
int			check_foot_press_type(SDL_Event *event);

void		foot_panel_interaction_event(t_rt *rt_data, SDL_Event *event);
void		filter_panel_interaction_event(t_rt *rt_data, SDL_Event *event);

void		create_gui(t_rt *rt_data, SDL_Event *event, int flag);
int			check_if_in_gui(t_rt *rt_data, SDL_Event *event);
int			mouse_click_event(t_rt *rt_data, SDL_Event *event);

void		cone_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag, t_objects *sphere);
void		cylinder_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag, t_objects *sphere);
void		sphere_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag, t_objects *sphere);
void		arrows_active_unactive(t_rt *rt_data, SDL_Rect pos, float *min_max, float value);

char*		ftoa(float f, int tochnost);
void		blit_surface_data(t_rt *rt_data, float fdata, SDL_Rect *pos);

void		draw_sphere_info(t_rt *rt_data, t_objects *object);
void		draw_cylinder_info(t_rt *rt_data, t_objects *object);
void		draw_cone_info(t_rt *rt_data, t_objects *object);
void		draw_object_info(t_rt *rt_data, int i);
void		sdl_error(char *str);

void		init_gui_bmps(t_rt *rt_data);
void		init_foot_gui_bmps(t_rt *rt_data);
void		init_bar_positions(t_rt	*rt_data);

void		draw_clicked_info(t_rt *rt_data);
void		draw_filter_bar(t_rt *rt_data);
void		draw_foot_info(t_rt *rt_data);
void		draw_bar(t_rt *rt_data);
void		draw_gui(t_rt *rt_data);

void		make_screenshot(t_rt *rt_data);
void		swap_cartoon(t_intersect closest_inter, t_rt *rt_data, int i);
void		init_arrays(t_rt *rt_data);

uint32_t	rgb_to_int(t_channel rgb);
void		perlin_noise_disruption(SDL_Surface *surface);
void		plasma_disruption(SDL_Surface *surface);
void		check_mate_disruption(SDL_Surface *surface);
#endif
