/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wael-mos <wael-mos@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/28 10:54:10 by wael-mos          #+#    #+#             */
/*   Updated: 2020/07/30 17:03:56 by achoquel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_H
# define RT_H

# include "libft.h"
# include <gtk/gtk.h>
# include <stdint.h>
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <float.h>
# include <libxml/parser.h>
# include <stdio.h>
# include <string.h>
# include <libxml/encoding.h>
# include <libxml/xmlwriter.h>

# define CL_SILENCE_DEPRECATION
# ifdef __APPLE__
#  include <OpenCL/cl.h>
# elif defined __linux__
#  include <CL/cl.h>
# endif

# define CL_KERNEL_SOURCE "srcs/kernel/kernel.cl"
# define CL_ERROR_BUFF 65536
# define CL_COMPILE_FLAGS "-Werror"
# define MY_ENCODING "UTF-8"

# define SUCCESS 0
# define FAILURE 1

# define MAX_OBJECTS 100
# define MAX_LIGHTS 10
# define ESC_KEY 65307
# define KEYRELEASE 3
# define DESTROYNOTIFY 17

typedef struct				s_ray
{
	cl_float3				ori;
	cl_float3				dir;
}							t_ray;

typedef struct				s_cam
{
	cl_float3				pos;
	cl_float3				rot;
	cl_float				fov;
}							t_cam;

typedef struct				s_light
{
	cl_float3				pos;
	cl_float3				col;
	char					*id;
}							t_light;

typedef enum				e_type
{
	PLANE = 0,
	SPHERE,
	CYLINDER,
	CONE,
	TORE,
	DISK,
	PARA,
	CUBE,
}							t_type;

typedef struct				s_water
{
	cl_float				frequency;
	cl_float				ampli;
	int						mode;
}							t_water;

typedef struct				s_perlin
{
	cl_int					type;
	cl_int					octav;
	cl_float				turbpow;
	cl_float				scaler;
	cl_float				opacity;
	cl_int					ringnb;
	cl_int					linex;
	cl_int					liney;
}							t_perlin;

typedef struct				s_obj
{
	t_type					type;
	cl_float3				pos;
	cl_float				rad;
	cl_float3				rot;
	cl_float3				axe;
	cl_float3				col;
	cl_float				ior;
	cl_float				refl;
	cl_float				refr;
	t_water					water;
	t_perlin				perlin;
	cl_int					shine;
	cl_int					inf;
	cl_int					height;
	cl_int					checkh;
	cl_int					checkw;
	cl_float3				checkcol;
	char					*id;
}							t_obj;

typedef struct				s_scene
{
	cl_int					win_x;
	cl_int					win_y;
	t_cam					cam;
	cl_float				ambient;
	cl_int					effect;
	cl_float				saturation;
	cl_float				gamma;
	cl_int					selected_obj;
	cl_int					selected_light;
	cl_int					num_light;
	cl_int					num_obj;
	t_light					lights[MAX_LIGHTS];
	t_obj					objs[MAX_OBJECTS];
	cl_float3				bg;
	cl_int					bouncenb;
	cl_float3				fogcol;
	cl_float				fogdist;
}							t_scene;

typedef struct				s_cl
{
	cl_device_id			device_id;
	cl_context				context;
	cl_command_queue		command_queue;
	cl_program				program;
	cl_kernel				kernel;
	cl_mem					img;
	cl_mem					scene;
}							t_cl;

typedef struct				s_gtk
{
	GtkBuilder				*builder;
	GtkWidget				*window;
	GtkCssProvider			*css_provider;
	GdkPixbuf				*image;
	GtkImage				*render;
	unsigned int			*data;
	GtkWidget				*screenshot;
	GtkWidget				*newscene;
	GtkWidget				*filelist;
	GtkWidget				*openfile;
	GtkWidget				*savefile;
	GtkWidget				*addsphere;
	GtkWidget				*addcyl;
	GtkWidget				*addcone;
	GtkWidget				*addplane;
	GtkWidget				*adddisk;
	GtkWidget				*addtore;
	GtkWidget				*addcube;
	GtkWidget				*addcubet;
	GtkWidget				*addhyper;
	GtkWidget				*addpara;
	GtkWidget				*addlight;
	GtkWidget				*deleteobj;
	GtkWidget				*deletelight;
	GtkWidget				*objss;
	GtkWidget				*objs;
	GtkWidget				*swbox;
	GtkWidget				*lightsarea;
	GtkWidget				*objectlist;
	GtkWidget				*xpos;
	GtkWidget				*ypos;
	GtkWidget				*zpos;
	GtkWidget				*xrot;
	GtkWidget				*yrot;
	GtkWidget				*zrot;
	GtkWidget				*infswitch;
	GtkWidget				*height;
	GtkWidget				*heightlabel;
	GtkWidget				*radius;
	GtkWidget				*radiuslabel;
	GtkWidget				*outerrad;
	GtkWidget				*outerradlabel;
	GtkWidget				*objcolor;
	GtkWidget				*reflection;
	GtkWidget				*refraction;
	GtkWidget				*fresnel;
	GtkWidget				*reflectionset;
	GtkWidget				*refrset;
	GtkWidget				*specular;
	GtkWidget				*checkh;
	GtkWidget				*checkw;
	GtkWidget				*checkcol;
	GtkWidget				*ior;
	GtkWidget				*swexp;
	GtkWidget				*swfreq;
	GtkWidget				*swamp;
	GtkWidget				*swsea;
	GtkWidget				*swlake;
	GtkWidget				*infbox;
	GtkWidget				*heightbox;
	GtkWidget				*checkbox;
	GtkWidget				*perlinwood;
	GtkWidget				*perlinmarble;
	GtkWidget				*perlincloud;
	GtkWidget				*scaler;
	GtkWidget				*opacity;
	GtkWidget				*octave;
	GtkWidget				*turbpow;
	GtkWidget				*ringnb;
	GtkWidget				*linex;
	GtkWidget				*liney;
	GtkWidget				*lightbox;
	GtkWidget				*lightposx;
	GtkWidget				*lightposy;
	GtkWidget				*lightposz;
	GtkWidget				*lightrotx;
	GtkWidget				*lightroty;
	GtkWidget				*lightrotz;
	GtkWidget				*lightpar;
	GtkWidget				*lightdir;
	GtkWidget				*lightcol;
	GtkWidget				*lightexp;
	GtkWidget				*camposx;
	GtkWidget				*camposy;
	GtkWidget				*camposz;
	GtkWidget				*camrotx;
	GtkWidget				*camroty;
	GtkWidget				*camrotz;
	GtkWidget				*effsepia;
	GtkWidget				*effgrayscale;
	GtkWidget				*effinverted;
	GtkWidget				*effcell;
	GtkWidget				*desaturate;
	GtkWidget				*gamma;
	GtkWidget				*fov;
	GtkWidget				*ambient;
	GtkWidget				*backgroundcolor;
	GtkWidget				*bounce;
	GtkWidget				*checktitle;
	GtkWidget				*thtitle;
	GtkWidget				*twtitle;
	GtkWidget				*tcoltitle;
	GtkWidget				*objr;
	GtkWidget				*objg;
	GtkWidget				*objb;
	GtkWidget				*checkr;
	GtkWidget				*checkg;
	GtkWidget				*checkb;
	GtkWidget				*lightr;
	GtkWidget				*lightg;
	GtkWidget				*lightb;
	GtkWidget				*bgr;
	GtkWidget				*bgg;
	GtkWidget				*bgb;
	GtkWidget				*fogr;
	GtkWidget				*fogg;
	GtkWidget				*fogb;
	GtkWidget				*fogdist;
}							t_gtk;

typedef struct				s_env
{
	t_gtk					gtk;
	t_cl					cl;
	t_scene					scene;
}							t_env;

cl_float3					rotate_x(cl_float3 v, double theta);
cl_float3					rotate_y(cl_float3 v, double theta);
cl_float3					rotate_z(cl_float3 v, double theta);
cl_float3					rotate_full(cl_float3 ori, cl_float3 rot);
cl_float3					deg(cl_float3 rot);
cl_float3					vec(float x, float y, float z);
float						dot(cl_float3 v1, cl_float3 v2);
cl_float3					normalize(cl_float3 v);
cl_float3					get_axe(cl_float3 rot);

int							parsing(char *av, t_scene *scene);
void						parse_windows(xmlNode *node, t_scene *scene);
void						parse_effects(xmlNode *node, t_scene *scene);
void						parse_cam(xmlNode *node, t_scene *scene);
int							parse_lights(xmlNode *node, t_scene *scene);
int							parse_objects(xmlNode *node, t_scene *scene);
void						parse_anobj(xmlNode *node, t_obj *obj);
t_type						read_type(char *word);
void						check_value(t_scene *scene);
cl_float3					parse_pos(xmlNode *cur);
cl_float3					parse_rot(xmlNode *cur);
cl_float3					parse_col(xmlNode *cur);
t_water						parse_water(xmlNode *cur);
t_perlin					parse_perlin(xmlNode *node);

void						our_exit(t_env *env, int status, char *msg);
void						cl_init(t_env *env);
void						cl_prepare_mem(t_env *env);
void						cl_run_kernel(t_env *env);
void						cl_error(t_env *env, char *err_msg);
void						cl_cleanup(t_cl *cl);
void						create_lids(t_scene *scene);
void						create_oids(t_scene *scene);
gboolean					cross_exit(GtkWidget *widget, gpointer data);
gboolean					screenshot(GtkButton *btn, gpointer data);
void						widget_init_sinewave(t_env *env);
void						widget_init_buttons1(t_env *env);
void						widget_init_buttons2(t_env *env);
void						widget_init_perlin(t_env *env);
void						widget_init_master(t_env *env);
void						widget_init_camera(t_env *env);
void						widget_init_effect(t_env *env);
void						widget_init_lists(t_env *env);
void						widget_init_objpart1(t_env *env);
void						widget_init_objpart2(t_env *env);
void						widget_init_light(t_env *env);
gboolean					sw_seamode(GtkSwitch *btn, GParamSpec *pspec, \
							gpointer data);
gboolean					sw_lakemode(GtkSwitch *btn, GParamSpec *pspec, \
							gpointer data);
gboolean					sw_freq(GtkSpinButton *btn, gpointer data);
gboolean					sw_amp(GtkSpinButton *btn, gpointer data);
void						init_sinewave_values(t_env *env, int i);
gboolean					perlin_wood(GtkSwitch *btn, GParamSpec *pspec, \
							gpointer data);
gboolean					perlin_marble(GtkSwitch *btn, GParamSpec *pspec, \
							gpointer data);
gboolean					perlin_cloud(GtkSwitch *btn, GParamSpec *pspec, \
							gpointer data);
gboolean					perlin_scaler(GtkSpinButton *btn, gpointer data);
gboolean					perlin_octave(GtkSpinButton *btn, gpointer data);
gboolean					perlin_opacity(GtkSpinButton *btn, gpointer data);
gboolean					perlin_turbpow(GtkSpinButton *btn, gpointer data);
gboolean					perlin_ringnb(GtkSpinButton *btn, gpointer data);
gboolean					perlin_linex(GtkSpinButton *btn, gpointer data);
gboolean					perlin_liney(GtkSpinButton *btn, gpointer data);
void						init_perlin_values(t_env *env, int i);
void						init_objectbox(t_env *env);
void						content_hider(t_env *env, int i);
void						init_general(t_env *env, int i);
void						init_material(t_env *env, int i);
gboolean					none_init(t_env *env);
gboolean					obj_init(t_env *env, char *id);
gboolean					init_selectedobject_values(GtkComboBoxText *cbbt, \
							gpointer data);
gboolean					move_objx(GtkSpinButton *btn, gpointer data);
gboolean					move_objy(GtkSpinButton *btn, gpointer data);
gboolean					move_objz(GtkSpinButton *btn, gpointer data);
gboolean					rot_objx(GtkSpinButton *btn, gpointer data);
gboolean					rot_objy(GtkSpinButton *btn, gpointer data);
gboolean					rot_objz(GtkSpinButton *btn, gpointer data);
gboolean					change_refl(GtkSpinButton *btn, gpointer data);
gboolean					change_refr(GtkSpinButton *btn, gpointer data);
gboolean					change_ior(GtkSpinButton *btn, gpointer data);
gboolean					change_radius(GtkSpinButton *btn, gpointer data);
gboolean					change_col(GtkColorButton *btn, gpointer data);
gboolean					init_light(t_env *env, char *id);
gboolean					init_selectedlight_values(GtkComboBoxText *cbbt, \
							gpointer data);
void						init_lightbox(t_env *env);
gboolean					move_lightx(GtkSpinButton *btn, gpointer data);
gboolean					move_lighty(GtkSpinButton *btn, gpointer data);
gboolean					move_lightz(GtkSpinButton *btn, gpointer data);
gboolean					change_lcol(GtkColorButton *btn, gpointer data);
gboolean					key_handler(GtkWidget *widget, GdkEventKey *event, \
							gpointer data);
void						callback_init_effect(t_env *env);
void						callback_init_light(t_env *env);
void						obj_hide_show(t_env *env, int i);
void						callback_init_perlin(t_env *env);
void						callback_init_master(t_env *env);
void						callback_init_button1(t_env *env);
void						callback_init_button2(t_env *env);
void						callback_init_objpart1(t_env *env);
void						callback_init_objpart2(t_env *env);
void						callback_init_camera(t_env *env);
gboolean					change_bgcol(GtkColorButton *btn, gpointer data);
gboolean					change_bounce(GtkSpinButton *btn, gpointer data);
gboolean					change_effect(GtkComboBoxText *cbbt, gpointer data);
gboolean					change_saturation(GtkSpinButton *btn, \
							gpointer data);
gboolean					change_gamma(GtkSpinButton *btn, gpointer data);
void						init_properties_norm(t_env *env);
void						init_camproperties_values(t_env *env);
gboolean					rot_camy(GtkSpinButton *btn, gpointer data);
gboolean					rot_camz(GtkSpinButton *btn, gpointer data);
gboolean					change_fov(GtkSpinButton *btn, gpointer data);
gboolean					change_ambient(GtkSpinButton *btn, gpointer data);
float						rad2deg(float rad);
gboolean					move_camx(GtkSpinButton *btn, gpointer data);
gboolean					move_camy(GtkSpinButton *btn, gpointer data);
gboolean					move_camz(GtkSpinButton *btn, gpointer data);
gboolean					rot_camx(GtkSpinButton *btn, gpointer data);
void						block_3(t_env *env);
void						blocker_master(t_env *env);
void						unblocker_master(t_env *env);
void						unblock_1(t_env *env);
void						unblock_2(t_env *env);
void						unblock_3(t_env *env);
void						block_1(t_env *env);
void						block_2(t_env *env);
void						init_new_scene(t_env *env, int state);
gboolean					new_scene(GtkButton *btn, gpointer data);
gboolean					add_cone(GtkButton *btn, gpointer data);
gboolean					add_para(GtkButton *btn, gpointer data);
gboolean					add_plane(GtkButton *btn, gpointer data);
gboolean					add_disk(GtkButton *btn, gpointer data);
gboolean					new_light(GtkButton *btn, gpointer data);
t_obj						create_object(int id);
t_light						create_light(void);
int							add_object(t_env *env, int id);
gboolean					add_sphere(GtkButton *btn, gpointer data);
gboolean					add_cyl(GtkButton *btn, gpointer data);
gboolean					openfile(GtkButton *btn, gpointer data);
void						init_openfile_list(t_env *env);
gboolean					delete_anobj(GtkButton *btn, gpointer data);
gboolean					delete_alight(GtkButton *btn, gpointer data);
int							exporter_main(t_scene *scene);
int							exporter_objects(xmlTextWriterPtr writer, \
							t_scene *scene);
int							exporter_camera(xmlTextWriterPtr writer, \
							t_scene *scene);
int							exporter_lights(xmlTextWriterPtr writer, \
							t_scene *scene);
int							export_perlin(xmlTextWriterPtr writer, \
							t_scene *scene, int i);
int							export_water(xmlTextWriterPtr writer, \
							t_scene *scene, int i);
int							export_effects(xmlTextWriterPtr writer, \
							t_scene *scene);
int							export_objrad(xmlTextWriterPtr writer, \
							t_scene *scene, int i);
int							export_objpos(xmlTextWriterPtr writer, \
							t_scene *scene, int i);
const char					*exporter_get_objtype(t_obj object);
gboolean					change_height(GtkSpinButton *btn, gpointer data);
gboolean					change_specular(GtkSpinButton *btn, gpointer data);
void						change_infinite(GtkSwitch *btn, GParamSpec *pspec, \
							gpointer data);
void						effect_sepia(GtkSwitch *btn, GParamSpec *pspec, \
							gpointer data);
void						effect_grayscale(GtkSwitch *btn, GParamSpec *pspec,\
							gpointer data);
void						effect_inverted(GtkSwitch *btn, GParamSpec *pspec,\
							gpointer data);
void						effect_cellshading(GtkSwitch *btn,\
							GParamSpec *pspec, gpointer data);
gboolean					change_checkh(GtkSpinButton *btn, gpointer data);
gboolean					change_checkw(GtkSpinButton *btn, gpointer data);
gboolean					change_checkcol(GtkColorButton *btn, gpointer data);
gboolean					savefile(GtkButton *btn, gpointer data);
void						init_objectbox(t_env *env);
gboolean					change_col(GtkColorButton *btn, gpointer data);
gboolean					change_height(GtkSpinButton *btn, gpointer data);
void						init_obj(t_env *env, int i);
int							export_itoa(xmlTextWriterPtr writer,\
								char *name, float data);
void						init_effects(t_env *env);
void						change_effswitch_state(t_env *env);
void						pattern_hider(t_env *env, int i);
gboolean					add_tore(GtkButton *btn, gpointer data);
gboolean					add_goursat(GtkButton *btn, gpointer data);
void						end_oids(t_scene *scene, int i);
gboolean					change_objr(GtkSpinButton *btn, gpointer data);
gboolean					change_objg(GtkSpinButton *btn, gpointer data);
gboolean					change_objb(GtkSpinButton *btn, gpointer data);
gboolean					change_checkr(GtkSpinButton *btn, gpointer data);
gboolean					change_checkg(GtkSpinButton *btn, gpointer data);
gboolean					change_checkb(GtkSpinButton *btn, gpointer data);
gboolean					change_bgr(GtkSpinButton *btn, gpointer data);
gboolean					change_bgg(GtkSpinButton *btn, gpointer data);
gboolean					change_bgb(GtkSpinButton *btn, gpointer data);
gboolean					change_lightr(GtkSpinButton *btn, gpointer data);
gboolean					change_lightg(GtkSpinButton *btn, gpointer data);
gboolean					change_lightb(GtkSpinButton *btn, gpointer data);
void						block_5(t_env *env);
void						unblock_5(t_env *env);
gboolean					change_fogr(GtkSpinButton *btn, gpointer data);
gboolean					change_fogg(GtkSpinButton *btn, gpointer data);
gboolean					change_fogb(GtkSpinButton *btn, gpointer data);
gboolean					change_fogdist(GtkSpinButton *btn, gpointer data);
void						init_fog_values(t_env *env);
void						unblock_6(t_env *env);
void						block_6(t_env *env);

#endif
