#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern void moby_set_state(u8 *a, s32 b, s32 c);
extern f32 D_L07_001B17E0 __attribute__((sda));
extern f32 D_L07_001B17F0 __attribute__((sda));
extern f32 D_L07_001B1800 __attribute__((sda));
extern f32 D_L07_001B1810 __attribute__((sda));
extern f32 D_L07_001B1814;
extern f32 D_L07_001B1818;
extern f32 D_L07_001B1744 __attribute__((sda));
extern f32 D_L07_001B1748 __attribute__((sda));
extern u16 **D_L07_001A9014;
extern u8 *D_L07_001B2954;
extern s32 D_L07_001B1E90;
extern s32 g_music_state[];
extern char g_hero_position[];
extern f32 g_hero_state[];
extern void func_002A0F48(u8 *a);
extern void math_approach_target_with_braking(void *a, f32 b, f32 c, f32 d, f32 e);
extern void func_PAL_L00_002B9CD8(void *obj, void *pos, s32 a2, s32 a3);
extern f32 mat_fast_helper_a(f32 a, f32 b);
extern f32 vec_distance_xy(void *a, void *b);
extern void SetCamera5Pose(void *a, void *b, s32 c, s32 d, s32 e);
extern void moby_build_matrix(u8 *a);

/* Starts the second phase of the object: its two position vectors, the shared timer record, the
   effect call and the camera-facing vector, then raises bit 2 of every record of the group. */
void func_PAL_L07_00415638(u8 *a0, s32 group)
{
    f32 w[4];
    f32 t[4];
    u8 *state;
    u16 *p;
    u8 *e;
    f32 r;
    f32 *origin;

    moby_set_state(a0, 5, -1);
    qcopy(a0 + 0x10, &D_L07_001B17E0);
    qcopy(a0 + 0xF0, &D_L07_001B17F0);
    *(u16 *)(a0 + 0x34) &= 0xFFFD;
    func_002A0F48(a0);
    state = *(u8 **)(a0 + 0x68);
    g_music_state[9] = (*(s32 *)(state + 0xD4) & 0x3FFF) + 3000;
    g_music_state[10] = 0;
    math_approach_target_with_braking(state + 0x11C, 400.0f - D_L07_001B17E0, 5.0f,
                  D_L07_001B1748 * 0.00040000002f, D_L07_001B1744 * 0.020000001f);
    *(s32 *)(state + 0x16B0) = 0;
    *(s32 *)(state + 0xD0) = group;
    *(f32 *)(state + 0x16B8) = 1.0f;
    *(s32 *)(state + 0x16BC) = 0;
    func_PAL_L00_002B9CD8(&D_L07_001B1800, &D_L07_001B17F0, 0x6F, 1);
    *(TI128 *)t = *(TI128 *)g_hero_position;
    t[2] = t[2] + 1.0f;
    qzero_nc(w);
    origin = &D_L07_001B1810;
    w[2] = mat_fast_helper_a(g_hero_state[0x20] - D_L07_001B1810, g_hero_state[0x21] - D_L07_001B1814);
    r = vec_distance_xy(t, origin);
    w[1] = mat_fast_helper_a(r, D_L07_001B1818 - t[2]);
    SetCamera5Pose(origin, w, 1, 0, 0);
    moby_build_matrix(a0);
    for (p = D_L07_001A9014[group];
         p != 0 && ((s16)p[-1] >= 0 || p == D_L07_001A9014[group]) &&
         (e = D_L07_001B2954 + ((*p & 0x7FFF) << 5)) != 0;
         p++) {
        e[0x1E] |= 4;
    }
    D_L07_001B1E90 = 0;
}
