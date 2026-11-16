#include "names.h"
/* func_PAL_L02_00426700, the PAL copy of func_L02_004216F0: the same C, where scale func_00283CF0(D_L02_001B1FA4 / t). */

/* func_PAL_L02_00426700 is a unit of its own: it needs the opt-in quadword-copy profile and its
   scheduling barrier (-frac2-qcopy -frac2-qcopy-barrier, config/cflags.txt), which give retail's grouped `lq`/`sq`
   with register addresses and keep the instructions around the copy on their own side of it;
   -g gives the two nops retail has before its `div.s` (a -g unit's line labels). */

typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));

extern void *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void moby_rebuild_frame_from_transform(u8 *);
extern int PlayMobySound(int, int, void *);
extern char g_hero_state_block[];
extern float g_projectile_start_value __attribute__((sda));
extern float g_projectile_l02_speed __attribute__((sda));
extern float g_projectile_range __attribute__((sda));

u8 *func_PAL_L02_00426700(u8 *a0, int a1, u8 *a2, float a3) {
    u8 *obj = CreateMoby(0xD08);
    u8 *v;
    int n;
    float t;

    if (obj != 0) {
        *(u8 *)(obj + 0x20) = 0;
        *(u8 *)(obj + 0x30) = 0xFF;
        t = g_projectile_l02_speed * 0.020000001f;
        v = *(u8 **)(obj + 0x68);
        *(float *)(v + 0x64) = a3;
        vec_scale_to_length(v + 0x40, a2, t);
        *(TI128 *)(obj + 0x10) = *(TI128 *)a0;
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(v + 0x40);
        FastVecCross(obj + 0xD0, obj + 0xC0, g_hero_state_block);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, -1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        t = g_projectile_l02_speed * 0.020000001f;
        n = (((int)(FloatToInt(g_projectile_range / t)) * 5 + 2) / 6);
        *(int *)(v + 0x58) = n;
        *(float *)(v + 0x5C) = 1.0f / IntToFloat(n);
        *(int *)(v + 0x50) = a1;
        *(u8 *)(obj + 0x20) = 0;
        *(float *)(v + 0x60) = g_projectile_start_value;
        moby_rebuild_frame_from_transform(obj);
        PlayMobySound(1, 0, obj);
    }
    return obj;
}
