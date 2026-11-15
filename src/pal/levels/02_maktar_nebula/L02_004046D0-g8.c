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
extern float D_L02_001B148C[];
extern float D_L02_001B14BC[];
extern int D_L02_001B14A8 __attribute__((sda));
extern int D_L02_001B14AC __attribute__((sda));
extern int D_L02_001B14E4 __attribute__((sda));
extern int D_L02_001B14E8 __attribute__((sda));
extern int D_L02_001B14C0 __attribute__((sda));
extern float D_L02_001B14B0 __attribute__((sda));
extern float D_L02_001B14B8 __attribute__((sda));
extern float D_L02_001B14C4 __attribute__((sda));
extern float D_L02_001B14C8 __attribute__((sda));
extern float D_L02_001B14CC __attribute__((sda));
extern float D_L02_001B14D0 __attribute__((sda));
extern float D_L02_001B14D4 __attribute__((sda));
extern float D_L02_001B14D8 __attribute__((sda));
extern float D_L02_001B14DC __attribute__((sda));
extern float D_L02_001B14E0 __attribute__((sda));
extern float D_L02_001B1488[] SDATA(D_L02_001B1488);

/* Draws two passes of each radial strip and two facing quads at its inner end.
   UVs scroll over time while the complete set rotates. */
void func_PAL_L02_004046D0(char *obj) {
    float center[4], inner[4], outer[4], axis[4], ni[4], no[4];
    struct { float v[4][4]; unsigned color[4]; float uv[4][2]; char rest[32]; } quad;
    float temp[4];
    char *state=*(char **)(obj + 0x68);
    float angle=*(float *)(state + 0xDC);
    float step=6.283185482025146484375f / IntToFloat(D_L02_001B14C0);
    float alpha, size, halfSize;
    unsigned color;
    int i, j, kind;
    qcopy(center, arena_get_camera_point(obj));
    center[2]-=D_L02_001B14D8;
    for (i = 0; i < D_L02_001B14C0; i++) {
        qcopy(inner, center);
        inner[0]+=D_L02_001B14C8*math_fast_sin_or_cos_a(angle);
        inner[1]+=D_L02_001B14C8*math_fast_sin_or_cos_b(angle);
        qcopy(outer, center);
        outer[0]+=D_L02_001B14CC*math_fast_sin_or_cos_a(angle);
        outer[1]+=D_L02_001B14CC*math_fast_sin_or_cos_b(angle);
        FastVecSub(axis, inner, outer);
        FastVecSub(ni, inner, g_camera_l02_position);
        FastVecSub(no, outer, g_camera_l02_position);
        FastVecCross(ni, ni, axis);
        FastVecCross(no, no, axis);
        vec_scale_to_length(ni, ni, D_L02_001B14D0);
        vec_scale_to_length(no, no, D_L02_001B14D0);
        gfx_init_quad_packet_state(&quad, 0x17, 1, 0x80);
        alpha=math_random_float_range(D_L02_001B14B8, D_L02_001B14BC[0]);
        color=(D_L02_001B14A8 & 0xFFFFFF) | ((int)(alpha*(float)(int)((unsigned)D_L02_001B14A8>>24))<<24);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=color;
        for (j = 0; j < 4; j++) {
            quad.uv[j][0]=D_L02_001B1488[j*2]+*(float *)(state + 0xE0);
            quad.uv[j][1]=D_L02_001B148C[j*2];
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
        vec_scale_to_length(ni, ni, D_L02_001B14D4);
        vec_scale_to_length(no, no, D_L02_001B14D4);
        FastVecSub(temp, inner, ni);
        *(TI128 *)(quad.v[0])=*(TI128 *)(temp);
        FastVecAdd(temp, inner, ni);
        *(TI128 *)(quad.v[1])=*(TI128 *)(temp);
        FastVecSub(temp, outer, no);
        *(TI128 *)(quad.v[2])=*(TI128 *)(temp);
        FastVecAdd(temp, outer, no);
        *(TI128 *)(quad.v[3])=*(TI128 *)(temp);
        gfx_init_quad_packet_state(&quad, 0x2B, 1, 0x80);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=D_L02_001B14AC;
        draw_world_quad(&quad, 0, 0);
        size=math_random_float_range(D_L02_001B14DC, D_L02_001B14E0);
        halfSize=size*0.5f;
        kind=math_random_int_range(0x50, 0x60);
        alpha=math_random_angle();
        gfx_draw_aimed_effect_packet(inner, D_L02_001B14E4, halfSize, alpha, kind, 0x31, 2);
        size*=0.7f;
        kind=math_random_int_range(8, 0x16);
        alpha=math_random_angle();
        gfx_draw_aimed_effect_packet(inner, D_L02_001B14E8, size, alpha, kind, 0xB, 2);
        angle=FastAddRotations(angle, step);
    }
    *(float *)(state + 0xE0)+=D_L02_001B14B0;
    if (*(float *)(state + 0xE0)>1.0f) *(float *)(state + 0xE0)-=2.0f;
    if (*(float *)(state + 0xE0)<-1.0f) *(float *)(state + 0xE0)+=2.0f;
    *(float *)(state + 0xDC)+=D_L02_001B14C4*0.0003490659f;
    if (*(float *)(state + 0xDC)>step) *(float *)(state + 0xDC)=0;
}
