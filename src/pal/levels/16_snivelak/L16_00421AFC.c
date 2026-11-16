#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

extern f32 FastAddRotations(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern s32 vec_fast_helper_b(char *);
extern void rotation_cycle_apply_wobble_pal(char *);
extern void moby_set_state(char *, s32, s32);

/* func_PAL_L16_00421AFC, the PAL copy of func_L16_0041C7A0: the same C, where the two rates are scaled for 50 Hz. */
void rotation_cycle_update_pal(char *self) {
    char *vars = *(char **)(self + 0x68);
    f32 first_rate, second_rate, angle;
    switch (*(u8 *)(self + 0x20)) {
    case 0:
        *(s32 *)(vars + 0) = 0;
        *(s32 *)(vars + 4) = 0;
        *(s32 *)(vars + 8) = 0;
        *(s32 *)(vars + 12) = 0;
        *(s32 *)(vars + 16) = 0;
        first_rate = *(f32 *)(vars + 20);
        angle = *(f32 *)(self + 0xF0);
        second_rate = *(f32 *)(vars + 24);
        *(f32 *)(vars + 40) = angle;
        *(s32 *)(vars + 36) = *(u8 *)(self + 0xBC);
        *(f32 *)(vars + 28) = first_rate;
        *(f32 *)(vars + 32) = second_rate;
        *(f32 *)(vars + 20) = (first_rate * 5.0f + 2.0f) * 0.16666667f;
        *(f32 *)(vars + 24) = (second_rate * 5.0f + 2.0f) * 0.16666667f;
        moby_set_state(self, 1, -1);
        break;
    case 1:
        if (*(u8 *)(self + 0xBC))
            moby_set_state(self, 4, -1);
        break;
    case 4:
        if (*(s32 *)(vars + 16) < 180) {
            *(f32 *)(self + 0xF0) = FastAddRotations(*(f32 *)(self + 0xF0), 0.0872664749622345f);
            *(s32 *)(vars + 16) += 5;
        } else moby_set_state(self, 2, -1);
        break;
    case 2:
        if (vec_fast_helper_b(vars + 20)) moby_set_state(self, 3, -1);
        break;
    case 3:
        if (vec_fast_helper_b(vars + 24)) moby_set_state(self, 5, -1);
        rotation_cycle_apply_wobble_pal(self);
        break;
    case 5:
        if (*(s32 *)(vars + 16) > 0) {
            *(f32 *)(self + 0xF0) = fast_subtract_rotations(*(f32 *)(self + 0xF0), 0.0872664749622345f);
            *(s32 *)(vars + 16) -= 5;
        } else {
            *(u8 *)(self + 0xBC) = *(u8 *)(vars + 36);
            *(f32 *)(vars + 20) = (*(f32 *)(vars + 28) * 5.0f + 2.0f) * 0.16666667f;
            *(f32 *)(vars + 24) = (*(f32 *)(vars + 32) * 5.0f + 2.0f) * 0.16666667f;
            *(f32 *)(self + 0xF0) = *(f32 *)(vars + 40);
            moby_set_state(self, 1, -1);
        }
        break;
    }
}
