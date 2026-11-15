#include "common.h"

/* Level tuning words are read through $gp (-G8). The loop recomputes each index instead of
   stepping a pointer: this unit is built without strength reduction (config/cflags.txt). */

typedef int TI128 __attribute__((mode(TI)));

extern void gfx_set_gs_register_constant(char *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern float math_lerp_float(float, float, float);
extern void gfx_draw_billboard_quad_with_uv(void *, s32, s32, float, float, float);
extern s32 FloatToInt(float);
/* The entity pool pointer and the second tuning word are read absolutely. */
extern u8 *g_moby_l11_table[] __attribute__((sda));
extern float D_L11_001B1944[] __attribute__((sda));
extern float D_L11_001B1940 __attribute__((sda));
extern s32 D_L11_001B1948 __attribute__((sda));
extern float D_L11_001B194C __attribute__((sda));

/* The part of the state at +0x68 that this function reads: two four-float tables and the
   index of a 256-byte record of the entity pool. */
typedef struct {
    u8 pad00[0x90];
    float scale[4];     /* +0x90 */
    float level[4];     /* +0xA0 */
    u8 padB0[0x1D0 - 0xB0];
    s32 entity;         /* +0x1D0 */
} FourChannelState;

/* For each of the four channels: a vector (0, 0, level * scale) turned by the matrix at +0xC0 of
   the entity record and moved to its position (+0x10), then handed to func_002820D0 with a count
   that ramps up over the first tenth of the level and down after it. */
void part_spawn_channel_beam_effects(char *moby)
{
    FourChannelState *state = *(FourChannelState **)(moby + 0x68);
    float point[4];
    float offset[4];
    float angle;
    float level_value;
    s32 count;
    int i;

    gfx_set_gs_register_constant(moby);
    for (i = 0; i < 4; i++) {
        *(TI128 *)offset = 0;
        offset[2] = state->level[i] * state->scale[i];
        *(TI128 *)point = *(TI128 *)offset;
        matrix_mul_vec3(point, point, g_moby_l11_table[0] + (state->entity << 8) + 0xC0);
        FastVecAdd(point, point, g_moby_l11_table[0] + (state->entity << 8) + 0x10);
        angle = math_lerp_float(D_L11_001B1940, D_L11_001B1944[0], state->level[i]);
        level_value = state->level[i];
        if (level_value < 0.1f)
            count = FloatToInt((float)D_L11_001B1948 * level_value * 10.0f);
        else
            count = FloatToInt((float)D_L11_001B1948 * (1.0f - level_value));
        gfx_draw_billboard_quad_with_uv(point, count, 0, angle, D_L11_001B194C, 0.08f);
    }
}
