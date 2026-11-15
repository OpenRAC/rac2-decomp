#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
extern u8 D_001A7BC8[] __attribute__((sda));
extern u8 D_001A7BE0 __attribute__((sda));
extern char g_hero_position[];
extern int D_L06_001B2348 __attribute__((sda));
extern void moby_set_state(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern float FastVecLength(void *);
extern void moby_mark_flag_and_append_to_list(int);
extern float ApproachValue(float *, float, float);
extern void gfx_add_draw_callback_first(void *, void *);
extern void hud_show_pickup_notice(void);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
extern void vec_scale_to_length(void *, void *, float);
extern float math_fabs(float);
extern u8 g_hero_state[];

void func_PAL_L06_003E4348(u8 *moby)
{
    char *st = *(char **)(moby + 0x68);
    float scale, inverse;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30] = 0xFF;
        if (!D_001A7BC8[*(int *)st]) moby_set_state(moby, 1, -1);
        else moby_mark_spawned(moby);
        break;
    case 1:
        if (vec_distance_xy(moby + 0x10, g_hero_position) < 2.0f &&
            math_fabs(*(float *)(moby + 0x18) - *(float *)(g_hero_position + 8)) < 2.0f) {
            moby_mark_flag_and_append_to_list(*(int *)st);
            moby_set_state(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(st + 8) = 150;
        }
        if (*(int *)st == 24 && D_001A7BE0) {
            moby_mark_flag_and_append_to_list(24);
            moby_set_state(moby, 2, -1);
            *(u16 *)(moby + 0x34) |= 0x100;
            *(int *)(st + 8) = 150;
        }
        break;
    case 2:
        if ((*(u16 *)(moby + 0x34) ^ 1) & 1) {
            scale = FastVecLength(moby + 0xC0);
            ApproachValue(&scale, 0, 0.080000006f);
            inverse = 2.0f - scale;
            vec_scale_to_length(moby + 0xC0, moby + 0xC0, scale);
            vec_scale_to_length(moby + 0xD0, moby + 0xD0, scale);
            vec_scale_to_length(moby + 0xE0, moby + 0xE0, inverse);
            if (scale <= 0) {
                moby[0x31] = 0;
                *(u16 *)(moby + 0x34) |= 1;
            }
        }
        gfx_add_draw_callback_first(hud_show_pickup_notice, moby);
        if ((D_L06_001B2348 ^ 1) & 1) (*(int *)(st + 4))++;
        if (math_fast_float_d((int *)(st + 8))) {
            ApproachValue((float *)(st + 12), 0, 0.060000002f);
            if (*(float *)(st + 12) <= 0) moby_mark_spawned(moby);
        } else {
            ApproachValue((float *)(st + 12), 1, 0.060000002f);
        }
        break;
    }
}
