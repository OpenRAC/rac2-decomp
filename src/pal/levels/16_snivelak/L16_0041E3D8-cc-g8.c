/* func_PAL_L16_0041E3D8, the PAL copy of func_L16_00419140: the same C, where scale func_002A7820(D_L16_001B1C80, D_L16_001B1C84[0]); scale func_002A7820(D_L16_001B1C88[0], D_L16_001B1C8C[0]). */
#include "common.h"
extern f32 D_L16_001B1C60 __attribute__((sda));
extern f32 D_L16_001B1C70 __attribute__((sda));
extern s32 D_L16_001B1C78 __attribute__((sda));
extern s32 D_L16_001B1C80 __attribute__((sda));
extern s32 D_L16_001B1C90 __attribute__((sda));
extern f32 D_L16_001B1C64[] MACRO_ADDR;
extern f32 D_L16_001B1C68 __attribute__((nosda));
extern f32 D_L16_001B1C6C __attribute__((nosda));
extern f32 D_L16_001B1C74[] MACRO_ADDR;
extern s32 D_L16_001B1C7C[] MACRO_ADDR;
extern s32 D_L16_001B1C84[] MACRO_ADDR;
extern s32 D_L16_001B1C88[] MACRO_ADDR;
extern s32 D_L16_001B1C8C[] MACRO_ADDR;
extern void vec_random_direction(char *, f32, f32);
extern s32 math_random_int_range(s32, s32);
extern s32 math_random_int_below(s32);
extern char *part_spawn_hero_relative(char *, char *, u32, u32, f32, u32, u32);
extern void vec_clear_128(char *);
extern void FastVecAdd(char *, char *, char *);
extern f32 math_random_float_range(f32, f32);

/* Emits one central particle and the configured ring of falling particles. */
void func_PAL_L16_0041E3D8(char *self) {
    char velocity[16];
    char position[16];
    s32 i;
    s32 kind;
    s32 alpha;
    s32 firstKind;
    char *origin = self + 16;
    vec_random_direction(velocity, D_L16_001B1C60 * 0.020000001f,
                  D_L16_001B1C64[0] * 0.020000001f);
    firstKind = (((int)(math_random_int_range(D_L16_001B1C80, D_L16_001B1C84[0])) * 5 + 2) / 6) & 255;
    alpha = math_random_int_below(255);
    part_spawn_hero_relative(origin, velocity, D_L16_001B1C78, firstKind, D_L16_001B1C70, alpha & 255, 0);
    vec_clear_128(velocity);
    for (i = 0; i < D_L16_001B1C90; i++) {
        vec_random_direction(position, 0.0f, 0.25f);
        FastVecAdd(position, position, self + 16);
        *(f32 *)(velocity + 8) = -(math_random_float_range(D_L16_001B1C68, D_L16_001B1C6C) * 0.020000001f);
        kind = (((int)(math_random_int_range(D_L16_001B1C88[0], D_L16_001B1C8C[0])) * 5 + 2) / 6) & 255;
        alpha = math_random_int_below(255);
        part_spawn_hero_relative(position, velocity, D_L16_001B1C7C[0], kind, D_L16_001B1C74[0], alpha & 255, 0);
    }
}
