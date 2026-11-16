#include "names.h"
typedef int TI128 __attribute__((mode(TI)));
typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef short s16;

extern s32 g_record_list_count;
extern u16 **g_record_lists;
extern char *g_record_table;
extern char g_record_glow_marker_vec[8] __attribute__((sda));
extern char g_camera_l02_position[];

extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern float FastVecDot(void *, void *);
extern int math_lerp_int_fraction(int, int, float);
extern void gfx_l00_draw_billboard_quad(void *, int, float, float);

/* Draws glowing markers at nearby records that face the player. The closer they face, the brighter they get. */
void gfx_draw_record_glow_markers(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 listIndex = *(s32 *)(state + 0x104);
    u16 *listStart;
    u16 *entry;
    char *record;
    float v0[4];
    float v1[4];
    float v2[4];
    float v3[4];
    float dot;

    if (listIndex == -1)
        return;
    if (listIndex >= g_record_list_count)
        return;
    listStart = g_record_lists[listIndex];
    if (listStart == 0)
        return;
    entry = listStart;
    do {
        record = g_record_table + ((*entry & 0x7FFF) << 6);
        *(TI128 *)v0 = *(TI128 *)(record + 0x30);
        matrix_mul_vec3(v1, g_record_glow_marker_vec, record);
        FastVecAdd(v0, v0, v1);
        FastVecSub(v2, g_camera_l02_position, v0);
        vec_scale_to_length(v2, v2, 1.0f);
        FastVecScale(v3, record + 0x20, -1.0f);
        dot = FastVecDot(v2, v3);
        if (dot > 0.5f) {
            dot = dot - 0.5f;
            dot = dot + dot;
            gfx_l00_draw_billboard_quad(v0, math_lerp_int_fraction(0xFF8020, 0x88FF8020, dot * dot), 3.0f, 1.0f);
        }
    } while ((s16)*entry++ >= 0);
}
