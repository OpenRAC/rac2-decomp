#include "include_asm.h"

#include "common.h"
typedef struct {
    f32 x, y, z, w;
} Vec4458;
typedef struct {
    Vec4458 dir0;        
    u8 pad10[0xF0 - 0x10];
    Vec4458 velocity;    
    u8 pad100[0x270 - 0x100];
    s32 x270;
    u8 pad274[0x2290 - 0x274];
    s32 moby;            
    u8 pad2294[0x229C - 0x2294];
    s32 x229C;
    u8 pad22A0[0x22B4 - 0x22A0];
    u8 mode;             
} Hero4458;
typedef struct {
    u8 pad0[0x18];
    s32 x18;
    s32 hits;            
    u8 pad20[0x40 - 0x20];
    Vec4458 normal;      
} Hit4458;
extern Hero4458 g_hero_state;
extern Hit4458 g_collision_result;
extern float cam_get_view_space_vector_length(Vec4458 *);
extern void hero_build_relative_point(Vec4458 *, float, float, float, int);
extern float vec_length_xy(Vec4458 *);
extern void vec_scale_to_length(Vec4458 *, Vec4458 *, float);
extern void cam_set_view_space_height(Vec4458 *, Vec4458 *, float);
extern void FastVecScale(Vec4458 *, Vec4458 *, float);
extern void FastVecAdd(Vec4458 *, Vec4458 *, Vec4458 *);
extern int CollLine(Vec4458 *, Vec4458 *, int, s32, int);
extern int GetCollHitMaterial(void);
extern float cam_get_view_space_angle(Vec4458 *);
extern float FastVecDot(Vec4458 *, Vec4458 *);

/* While the hero moves, casts two short rays ahead of it (along its velocity, or along
 * the direction at +0x0 when nearly still or when forced): one from a point at the mode's
 * height, one from 0.3 of it reaching 1.4 times as far.  A slope of at least 50 degrees
 * under the first ray, or collision type 8 or 12 under the second, records the hit's word
 * at +0x18 in +0x270 and removes the part of the velocity at +0xF0 that runs into the
 * flattened surface normal. */
void func_PAL_L00_002B4380(int force)
{
    Vec4458 upper;
    Vec4458 upperEnd;
    Vec4458 lower;
    Vec4458 lowerEnd;
    float height;
    float reach;
    float slope;
    float dot;
    int type;

    if (cam_get_view_space_vector_length(&g_hero_state.velocity) < 0.002f)
        return;
    height = 0.37f;
    reach = 0.5f;
    if ((unsigned int)(g_hero_state.x229C - 17) < 2) {
        height = 0.0f;
        reach = 0.7f;
    } else if (g_hero_state.mode == 1) {
        height = 0.35f;
        reach = 0.27f;
    }
    hero_build_relative_point(&upper, 0.0f, 0.0f, height, 1);
    hero_build_relative_point(&lower, 0.0f, 0.0f, height * 0.3f, 1);
    if (force || vec_length_xy(&g_hero_state.velocity) < 0.01f) {
        vec_scale_to_length(&upperEnd, &g_hero_state.dir0, reach);
        vec_scale_to_length(&lowerEnd, &g_hero_state.dir0, reach * 1.4f);
    } else {
        cam_set_view_space_height(&upperEnd, &g_hero_state.velocity, 0.0f);
        vec_scale_to_length(&upperEnd, &upperEnd, reach);
        FastVecScale(&lowerEnd, &upperEnd, 1.4f);
    }
    type = -1;
    FastVecAdd(&upperEnd, &upperEnd, &upper);
    FastVecAdd(&lowerEnd, &lowerEnd, &lower);
    if (CollLine(&lower, &lowerEnd, 2, g_hero_state.moby, 0) && g_collision_result.hits > 0)
        type = GetCollHitMaterial();
    slope = 0.0f;
    if (CollLine(&upper, &upperEnd, 2, g_hero_state.moby, 0) && g_collision_result.hits > 0)
        slope = cam_get_view_space_angle(&g_collision_result.normal);
    if (slope >= 0.87266469f || type == 8 || type == 12) {
        g_hero_state.x270 = g_collision_result.x18;
        cam_set_view_space_height(&g_collision_result.normal, &g_collision_result.normal, 0.0f);
        vec_scale_to_length(&g_collision_result.normal, &g_collision_result.normal, 1.0f);
        dot = FastVecDot(&g_collision_result.normal, &g_hero_state.velocity);
        if (dot < 0.0f) {
            FastVecScale(&g_collision_result.normal, &g_collision_result.normal, -dot);
            FastVecAdd(&g_hero_state.velocity, &g_hero_state.velocity, &g_collision_result.normal);
        }
    }
}
