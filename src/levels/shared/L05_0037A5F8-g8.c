#include "names.h"
/* func_L05_0037A5F8: the HUD markers drawn over level objects (in levels 05, 10, 15, 25).
 * Own unit for -frac2-zero-ti-por (the rotation clear keeps its por + sq to 0($sp)). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float g_hud_marker_x __attribute__((sda));
extern float g_hud_marker_y __attribute__((sda));
extern float g_hud_marker_size __attribute__((sda));
extern float g_hud_marker_height __attribute__((sda));
extern int g_hud_marker_u __attribute__((sda));
extern int g_marker_quad_v_end __attribute__((sda));
extern float g_marker_default_radius __attribute__((sda));
extern int g_marker_texture_id __attribute__((sda));
extern float g_screen_l05_scale[] MACRO_ADDR;
extern u8 *g_level_object_list[] NOT_SDA;
extern u16 *g_spawn_list_table[];
extern u8 *g_feltzin_target_mobys[] MACRO_ADDR;
typedef struct { float position[4]; u8 pad[0x220]; float view[12]; } L05HudCamera;
extern L05HudCamera g_origin_vec;
extern u64 GetEffectTextureDescriptor(int);
extern void AppendSubpixelTexturedScreenQuad(float,float,float,float,int,int,int,int,u64,u64);
extern int level_get_saved_value(void);
extern char *moby_get_motion_data(u8 *);
extern float fast_vec_dist(void *,void *);
extern void euler_rotation_basis(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void mat_fast_helper_c(void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern float math_ease_out_quad(float);
extern int FloatToInt(float);
extern int g_label_mode;
/* The HUD label idiom, as in src/levels/15_gorn/L15_00431590-g8.c. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_label_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* label_y with the rounded result as its own handle. Its display-mode and result tests
 * have no effect (dead-test rounding helper, allowed by owner ruling of 7 November 2026,
 * precedent src/game/002D2188-g8.c); they set retail's block and register layout at entry. */
static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = g_label_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the small HUD markers over nearby objects, pointing toward them. */
void hud_draw_object_markers(void)
{
    float offset[4],rotation[4],rotate[12],view[12];
    float distance,x,y,scale,radius;
    u64 texture,color,color2;
    u8 *object,*state;
    u16 *list,*nextList;
    int i,alpha,c,ty;
    u8 *entry;
    y = (float)hud_coord(g_hud_marker_y, g_screen_l05_scale[0], 0.5f);
    texture = GetEffectTextureDescriptor(g_marker_texture_id);
    AppendSubpixelTexturedScreenQuad(g_hud_marker_x,y,g_hud_marker_size,g_hud_marker_height,0,0,g_hud_marker_u,g_marker_quad_v_end,0x80808080ULL,texture);
    for (i=0;i<level_get_saved_value();i++) {
        entry = g_level_object_list[i];
        nextList = g_spawn_list_table[entry[0x21]];
        if (!nextList) continue;
        list = nextList;
        do {
            object = g_feltzin_target_mobys[0]+((*list&0x7FFF)<<8);
            state = (u8 *)moby_get_motion_data(object);
            if (*(int *)(state+0x110) && *(int *)(state+0x14C)) {
                distance = fast_vec_dist(g_origin_vec.position,object+0x10);
                if (distance <= 128.0f) {
                    radius = g_marker_default_radius;
                    radius *= 0.0078125f;
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    scale = distance*radius;
                    euler_rotation_basis(rotate,rotation);
                    FastVecSub(offset,object+0x10,g_origin_vec.position);
                    vec_scale_to_length(offset,offset,scale);
                    mat_fast_helper_c(view,g_origin_vec.view);
                    matrix_mul_vec3(offset,offset,view);
                    matrix_mul_vec3(offset,offset,rotate);
                    alpha = FloatToInt(math_ease_out_quad(1.0f-distance*0.0078125f)*128.0f);
                    distance = offset[2]*0.125f+g_hud_marker_size*0.5f;
                    if (*(int *)(state+0x158)) { alpha=128; distance=g_hud_marker_size*0.5f; }
                    if (distance > g_hud_marker_size+g_hud_marker_size) distance=g_hud_marker_size+g_hud_marker_size;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+g_hud_marker_x;
                    ty = label_y((void *)alpha, g_hud_marker_y-offset[1], g_screen_l05_scale[0], 0.5f, 1);
                    y = (float)ty;
                    c = *(s32 *)(state+0x150);
                    c |= alpha<<24;
                    color = c;
                    texture = GetEffectTextureDescriptor(g_marker_texture_id);
                    AppendSubpixelTexturedScreenQuad(x,y,distance,distance,0,0,g_hud_marker_u,g_marker_quad_v_end,color,texture);
                } else if (*(int *)(state+0x158)) {
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    y = g_marker_default_radius;
                    euler_rotation_basis(rotate,rotation);
                    FastVecSub(offset,object+0x10,g_origin_vec.position);
                    vec_scale_to_length(offset,offset,y);
                    mat_fast_helper_c(view,g_origin_vec.view);
                    matrix_mul_vec3(offset,offset,view);
                    matrix_mul_vec3(offset,offset,rotate);
                    alpha=128;
                    distance = g_hud_marker_size;
                    if (distance > g_hud_marker_size+g_hud_marker_size) distance=g_hud_marker_size+g_hud_marker_size;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+g_hud_marker_x;
                    ty = label_y(state, g_hud_marker_y-offset[1], g_screen_l05_scale[0], 0.5f, 1);
                    y = (float)ty;
                    c = *(s32 *)(state+0x150);
                    c |= alpha<<24;
                    color2 = c;
                    texture = GetEffectTextureDescriptor(g_marker_texture_id);
                    AppendSubpixelTexturedScreenQuad(x,y,distance,distance,0,0,g_hud_marker_u,g_marker_quad_v_end,color2,texture);
                }
            }
        } while ((s16)*list++ >= 0);
    }
}
