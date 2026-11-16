#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float IntToFloat(int), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float), FastAddRotations(float, float);
extern float math_random_float_range(float, float), math_random_angle(void);
extern int math_random_int_range(int, int);
extern void *arena_get_camera_point(char *);
extern void FastVecSub(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void gfx_init_quad_packet_state(void *, int, int, int);
extern void draw_world_quad(void *, int, int);
extern void gfx_draw_aimed_effect_packet(void *, int, float, float, int, int, int);
extern float g_camera_l02_position[4];
extern float g_spark_quad_uv_v_table[];
extern float g_spark_alpha_max[];
extern int g_spark_base_color __attribute__((sda));
extern int g_spark_l02_quad_color __attribute__((sda));
extern int g_spark_inner_effect_param __attribute__((sda));
extern int g_spark_outer_effect_param __attribute__((sda));
extern int g_spark_segment_count __attribute__((sda));
extern float g_spark_uv_scroll_step __attribute__((sda));
extern float g_spark_alpha_min __attribute__((sda));
extern float g_spark_rotation_speed __attribute__((sda));
extern float g_spark_inner_radius __attribute__((sda));
extern float g_spark_outer_radius __attribute__((sda));
extern float g_spark_inner_normal_length __attribute__((sda));
extern float g_spark_outer_normal_length __attribute__((sda));
extern float g_spark_center_drop __attribute__((sda));
extern float g_spark_l02_size_min __attribute__((sda));
extern float g_spark_l02_size_max __attribute__((sda));
extern float g_spark_quad_uv_table[] SDATA(D_L02_001B1488);

/* Draws two passes of each radial strip and two facing quads at its inner end.
   UVs scroll over time while the complete set rotates. */
void DrawRadialQuadEffect_pal(char *obj) {
    float center[4], inner[4], outer[4], axis[4], ni[4], no[4];
    struct { float v[4][4]; unsigned color[4]; float uv[4][2]; char rest[32]; } quad;
    float temp[4];
    char *state=*(char **)(obj + 0x68);
    float angle=*(float *)(state + 0xDC);
    float step=6.283185482025146484375f / IntToFloat(g_spark_segment_count);
    float alpha, size, halfSize;
    unsigned color;
    int i, j, kind;
    qcopy(center, arena_get_camera_point(obj));
    center[2]-=g_spark_center_drop;
    for (i = 0; i < g_spark_segment_count; i++) {
        qcopy(inner, center);
        inner[0]+=g_spark_inner_radius*math_fast_sin_or_cos_a(angle);
        inner[1]+=g_spark_inner_radius*math_fast_sin_or_cos_b(angle);
        qcopy(outer, center);
        outer[0]+=g_spark_outer_radius*math_fast_sin_or_cos_a(angle);
        outer[1]+=g_spark_outer_radius*math_fast_sin_or_cos_b(angle);
        FastVecSub(axis, inner, outer);
        FastVecSub(ni, inner, g_camera_l02_position);
        FastVecSub(no, outer, g_camera_l02_position);
        FastVecCross(ni, ni, axis);
        FastVecCross(no, no, axis);
        vec_scale_to_length(ni, ni, g_spark_inner_normal_length);
        vec_scale_to_length(no, no, g_spark_inner_normal_length);
        gfx_init_quad_packet_state(&quad, 0x17, 1, 0x80);
        alpha=math_random_float_range(g_spark_alpha_min, g_spark_alpha_max[0]);
        color=(g_spark_base_color & 0xFFFFFF) | ((int)(alpha*(float)(int)((unsigned)g_spark_base_color>>24))<<24);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=color;
        for (j = 0; j < 4; j++) {
            quad.uv[j][0]=g_spark_quad_uv_table[j*2]+*(float *)(state + 0xE0);
            quad.uv[j][1]=g_spark_quad_uv_v_table[j*2];
        }
        FastVecSub(temp, inner, ni);
        *(TI128 *)(quad.v[0])=*(TI128 *)(temp);
        FastVecAdd(temp, inner, ni);
        *(TI128 *)(quad.v[1])=*(TI128 *)(temp);
        FastVecSub(temp, outer, no);
        *(TI128 *)(quad.v[2])=*(TI128 *)(temp);
        FastVecAdd(temp, outer, no);
        *(TI128 *)(quad.v[3])=*(TI128 *)(temp);
        draw_world_quad(&quad, 0, 0);
        vec_scale_to_length(ni, ni, g_spark_outer_normal_length);
        vec_scale_to_length(no, no, g_spark_outer_normal_length);
        FastVecSub(temp, inner, ni);
        *(TI128 *)(quad.v[0])=*(TI128 *)(temp);
        FastVecAdd(temp, inner, ni);
        *(TI128 *)(quad.v[1])=*(TI128 *)(temp);
        FastVecSub(temp, outer, no);
        *(TI128 *)(quad.v[2])=*(TI128 *)(temp);
        FastVecAdd(temp, outer, no);
        *(TI128 *)(quad.v[3])=*(TI128 *)(temp);
        gfx_init_quad_packet_state(&quad, 0x2B, 1, 0x80);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=g_spark_l02_quad_color;
        draw_world_quad(&quad, 0, 0);
        size=math_random_float_range(g_spark_l02_size_min, g_spark_l02_size_max);
        halfSize=size*0.5f;
        kind=math_random_int_range(0x50, 0x60);
        alpha=math_random_angle();
        gfx_draw_aimed_effect_packet(inner, g_spark_inner_effect_param, halfSize, alpha, kind, 0x31, 2);
        size*=0.7f;
        kind=math_random_int_range(8, 0x16);
        alpha=math_random_angle();
        gfx_draw_aimed_effect_packet(inner, g_spark_outer_effect_param, size, alpha, kind, 0xB, 2);
        angle=FastAddRotations(angle, step);
    }
    *(float *)(state + 0xE0)+=g_spark_uv_scroll_step;
    if (*(float *)(state + 0xE0)>1.0f) *(float *)(state + 0xE0)-=2.0f;
    if (*(float *)(state + 0xE0)<-1.0f) *(float *)(state + 0xE0)+=2.0f;
    *(float *)(state + 0xDC)+=g_spark_rotation_speed*0.0003490659f;
    if (*(float *)(state + 0xDC)>step) *(float *)(state + 0xDC)=0;
}
