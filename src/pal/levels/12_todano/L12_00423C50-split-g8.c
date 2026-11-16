#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern u8 *g_moby_list_start MACRO_ADDR;
extern void moby_set_state(void *, int, int);
extern s32 PlayMobySound(s32, s32, s32);
extern void matrix_mul_vec3(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern int IsPointInCuboid(void *, int);
extern char g_hero_position[];
extern char g_hero_prev_position[];
extern float vec_distance_xy(void *, void *);
extern int math_fast_float_d(void *);
extern float math_step_value_toward_target(void *, void *, float, float, float, float);
extern void FastVecScale(float, void *, void *);

/* Slides the door open while the hero or buddy is near its switch, and closes it again a moment after they leave (PAL: 50 Hz timings). */
void secret_door_update_pal(u8 *moby)
{
    s32 *vars = *(s32 **)(moby + 0x68);
    int state = moby[0x20];
    f32 open_offset[4];

    switch (state) {
    case 0:
        qcopy((u8 *)vars + 0x10, moby + 0x10);
        moby_set_state(moby, 1, -1);
        moby[0x30] = 0x7F;
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, g_moby_list_start + (vars[0] << 8) + 0x10) < 5.0f) {
            vars[0xB] = state;
            vars[8] = 0x32;
        } else if ((IsPointInCuboid(g_hero_position, vars[1]) && vars[0xB] != 0) ||
                   (IsPointInCuboid(g_hero_prev_position, vars[1]) && vars[0xB] != 0)) {
            vars[8] = 0x32;
        }
        if (math_fast_float_d((u8 *)vars + 0x20))
            math_step_value_toward_target((u8 *)vars + 0x24, (u8 *)vars + 0x28, 0.0f, 0.00080000004f, 0.00080000004f, 0.080000006f);
        else
            math_step_value_toward_target((u8 *)vars + 0x24, (u8 *)vars + 0x28, 1.0f, 0.00080000004f, 0.00080000004f, 0.080000006f);
        if (*(f32 *)((u8 *)vars + 0x28) != 0.0f) {
            *(TI128 *)open_offset = 0;
            open_offset[0] = 1.0f;
            open_offset[2] = 3.0f;
            matrix_mul_vec3(open_offset, open_offset, moby + 0xC0);
            FastVecScale(*(f32 *)((u8 *)vars + 0x24), open_offset, open_offset);
            FastVecAdd(moby + 0x10, (u8 *)vars + 0x10, open_offset);
            if (vars[0xC] % 120 == 0)
                PlayMobySound(0, 0, (s32)moby);
            vars[0xC]++;
        } else {
            vars[0xC] = 0;
        }
        break;
    }
}
