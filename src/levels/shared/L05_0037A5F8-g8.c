/* func_L05_0037A5F8: the HUD markers drawn over level objects (in levels 05, 10, 15, 25).
 * Own unit for -frac2-zero-ti-por (the rotation clear keeps its por + sq to 0($sp)). */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float D_L05_001AC4E0 __attribute__((sda));
extern float D_L05_001AC4E4 __attribute__((sda));
extern float D_L05_001AC4E8 __attribute__((sda));
extern float D_L05_001AC4EC __attribute__((sda));
extern int D_L05_001AC4F0 __attribute__((sda));
extern int D_L05_001AC4F4 __attribute__((sda));
extern float D_L05_001AC4F8 __attribute__((sda));
extern int D_L05_001AC4FC __attribute__((sda));
extern float D_L05_001B2D84[] MACRO_ADDR;
extern u8 *D_L05_00225DD0[] NOT_SDA;
extern u16 *D_L05_001FB220[];
extern u8 *D_L05_001B251C[] MACRO_ADDR;
typedef struct { float position[4]; u8 pad[0x220]; float view[12]; } L05HudCamera;
extern L05HudCamera D_L05_001B96C0;
extern u64 GetEffectTextureDescriptor(int);
extern void AppendSubpixelTexturedScreenQuad(float,float,float,float,int,int,int,int,u64,u64);
extern int level_get_saved_value(void);
extern s32 moby_get_motion_data(u8 *);
extern float fast_vec_dist(void *,void *);
extern void euler_rotation_basis(void *,void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_scale_to_length(void *,void *,float);
extern void mat_fast_helper_c(void *,void *);
extern void matrix_mul_vec3(void *,void *,void *);
extern float math_ease_out_quad(float);
extern int FloatToInt(float);
extern int D_L05_001B2D80;
/* The HUD label idiom, as in src/levels/15_gorn/L15_00431590-g8.c. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L05_001B2D80;
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
    int mode = D_L05_001B2D80;
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
    y = (float)hud_coord(D_L05_001AC4E4, D_L05_001B2D84[0], 0.5f);
    texture = GetEffectTextureDescriptor(D_L05_001AC4FC);
    AppendSubpixelTexturedScreenQuad(D_L05_001AC4E0,y,D_L05_001AC4E8,D_L05_001AC4EC,0,0,D_L05_001AC4F0,D_L05_001AC4F4,0x80808080ULL,texture);
    for (i=0;i<level_get_saved_value();i++) {
        entry = D_L05_00225DD0[i];
        nextList = D_L05_001FB220[entry[0x21]];
        if (!nextList) continue;
        list = nextList;
        do {
            object = D_L05_001B251C[0]+((*list&0x7FFF)<<8);
            state = (u8 *)moby_get_motion_data(object);
            if (*(int *)(state+0x110) && *(int *)(state+0x14C)) {
                distance = fast_vec_dist(D_L05_001B96C0.position,object+0x10);
                if (distance <= 128.0f) {
                    radius = D_L05_001AC4F8;
                    radius *= 0.0078125f;
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    scale = distance*radius;
                    euler_rotation_basis(rotate,rotation);
                    FastVecSub(offset,object+0x10,D_L05_001B96C0.position);
                    vec_scale_to_length(offset,offset,scale);
                    mat_fast_helper_c(view,D_L05_001B96C0.view);
                    matrix_mul_vec3(offset,offset,view);
                    matrix_mul_vec3(offset,offset,rotate);
                    alpha = FloatToInt(math_ease_out_quad(1.0f-distance*0.0078125f)*128.0f);
                    distance = offset[2]*0.125f+D_L05_001AC4E8*0.5f;
                    if (*(int *)(state+0x158)) { alpha=128; distance=D_L05_001AC4E8*0.5f; }
                    if (distance > D_L05_001AC4E8+D_L05_001AC4E8) distance=D_L05_001AC4E8+D_L05_001AC4E8;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+D_L05_001AC4E0;
                    ty = label_y((void *)alpha, D_L05_001AC4E4-offset[1], D_L05_001B2D84[0], 0.5f, 1);
                    y = (float)ty;
                    c = *(s32 *)(state+0x150);
                    c |= alpha<<24;
                    color = c;
                    texture = GetEffectTextureDescriptor(D_L05_001AC4FC);
                    AppendSubpixelTexturedScreenQuad(x,y,distance,distance,0,0,D_L05_001AC4F0,D_L05_001AC4F4,color,texture);
                } else if (*(int *)(state+0x158)) {
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    y = D_L05_001AC4F8;
                    euler_rotation_basis(rotate,rotation);
                    FastVecSub(offset,object+0x10,D_L05_001B96C0.position);
                    vec_scale_to_length(offset,offset,y);
                    mat_fast_helper_c(view,D_L05_001B96C0.view);
                    matrix_mul_vec3(offset,offset,view);
                    matrix_mul_vec3(offset,offset,rotate);
                    alpha=128;
                    distance = D_L05_001AC4E8;
                    if (distance > D_L05_001AC4E8+D_L05_001AC4E8) distance=D_L05_001AC4E8+D_L05_001AC4E8;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+D_L05_001AC4E0;
                    ty = label_y(state, D_L05_001AC4E4-offset[1], D_L05_001B2D84[0], 0.5f, 1);
                    y = (float)ty;
                    c = *(s32 *)(state+0x150);
                    c |= alpha<<24;
                    color2 = c;
                    texture = GetEffectTextureDescriptor(D_L05_001AC4FC);
                    AppendSubpixelTexturedScreenQuad(x,y,distance,distance,0,0,D_L05_001AC4F0,D_L05_001AC4F4,color2,texture);
                }
            }
        } while ((s16)*list++ >= 0);
    }
}
