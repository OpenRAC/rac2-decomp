#include "include_asm.h"
#include "names.h"



typedef unsigned char u8;
typedef unsigned int u32;
typedef int s32;
extern u8 D_001C97C0[];
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 D_0019B2E8[];
extern s32 IsPointInCuboid(u8 *, s32);
extern s32 CollLine(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4);
extern u8 *g_moby_l18_table[] __attribute__((sda));
extern s32 D_L18_001B2838[] __attribute__((sda));
extern u8 D_00190000[];
extern void snd_stop_voice(s32 arg0);
extern void PlayMobySound(s32 arg0, s32 arg1, u8 *arg2);
extern void moby_mark_spawned(void *arg0);
extern void SpawnExplosion(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                           s32 arg6, s32 arg7, float arg8, float arg9, s32 arg10, s32 arg11,
                           s32 arg12, s32 arg13);

void func_PAL_L18_00437A28(u8 *a0) {
    u8 *s0;
    s32 a1;
    s0 = *(u8 **)(a0 + 0x68);
    a1 = *(s32 *)(s0 + 0x7F0);
    if (a1 != -1) {
        u8 *p = D_00190000 - 0x79A0 + a1 * 0x70;
        if (*(u32 *)(p + 0x88) != (u32)a0) goto end;
        if (p[0x74] == 0) goto end;
        snd_stop_voice(a1);
    }
end:
    *(s32 *)(s0 + 0x7F0) = -1;
    SpawnExplosion(a0 + 0x10, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1, 1.0f, 20.0f, 1, 1, 0, 0);
    PlayMobySound(6, 0, a0);
    if (*(u32 *)(s0 + 0x7C0)) {
        moby_mark_spawned(*(void **)(s0 + 0x7C0));
        *(u32 *)(s0 + 0x7C0) = 0;
    }
    if (*(u32 *)(s0 + 0x7C4)) {
        moby_mark_spawned(*(void **)(s0 + 0x7C4));
        *(u32 *)(s0 + 0x7C4) = 0;
    }
    if (*(u32 *)(s0 + 0x7C8)) {
        moby_mark_spawned(*(void **)(s0 + 0x7C8));
        *(u32 *)(s0 + 0x7C8) = 0;
    }
    moby_mark_spawned(a0);
}

